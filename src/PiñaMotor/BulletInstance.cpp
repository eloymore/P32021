#include "BulletInstance.h"
#include "Transform.h"
#include "MotorLoop.h"
#include "Entity.h"
#include "Rigidbody.h"
BulletInstance* BulletInstance::_bulletInstance = nullptr;

BulletInstance::BulletInstance() {
	
};

BulletInstance::~BulletInstance() {
	if(_world) delete _world;
	if(_broadphase) delete _broadphase;
	if(_collisionConfiguration) delete _collisionConfiguration;
	if(_dispatcher) delete _dispatcher;
	if(_solver) delete _solver;
}

BulletInstance* BulletInstance::GetInstance() {
	return _bulletInstance;
}

bool BulletInstance::Init() {
	if (_bulletInstance != nullptr) return false;
	_bulletInstance = new BulletInstance();
	_bulletInstance->initResources();
	return true;
}

void BulletInstance::initResources() {
	// Configuraci�n de Bullet
	try {
		_gravity = DEFAULT_GRAVITY;
		_broadphase = new btDbvtBroadphase();
		_collisionConfiguration = new btDefaultCollisionConfiguration();
		_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
		_solver = new btSequentialImpulseConstraintSolver();
		_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
		_world->setGravity(_gravity);
	}
	catch (std::exception& e) {
		throw e.what();
	}
}

void BulletInstance::removeCollisionEntity(Entity* ent)
{
	for (int i = 0; i < _collisions.size(); ++i) {
		if (_collisions[i].first == ent || _collisions[i].second == ent) {			
			_collisions[i] = _collisions[_collisions.size() - 1];
			_collisions.pop_back();
			i--;
		}			
	}
}

void BulletInstance::update()
{
	if (_paused)
		return;

	_world->stepSimulation(FIXED_UPDATE_TIME);

	//analizamos las colisiones de este frame del mundo de bullet para avisar
	//a onTriggerStart/Stay/End o onCollisionStart/Stay/End de los componentes de las entidades
	for (int i = 0; i < _dispatcher->getNumManifolds(); i++) {
		// Se consigue de la colision los dos rigidbodys
		btPersistentManifold* contactManifold = _dispatcher->getManifoldByIndexInternal(i);

		// Se cogen los datos del primer rigidbody
		const btCollisionObject* objectA = contactManifold->getBody0();
		const btRigidBody* rigidBodyA = btRigidBody::upcast(objectA);

		// Se cogen los datos del segundo rigidbody
		const btCollisionObject* objectB = contactManifold->getBody1();
		const btRigidBody* rigidBodyB = btRigidBody::upcast(objectB);

		// Cogemos nuestras entidades para decirles lo pertinente (si es la primera vez que colisiona o lleva mas veces)
		Entity* entA =static_cast<Entity*>(rigidBodyA->getUserPointer());
		Entity* entB = static_cast<Entity*>(rigidBodyB->getUserPointer());

		//Ya habia colisionado anteriormente
		if (find(entA,entB)) {			//si ninguno de los dos cuerpos es trigger, se lanza onCollisionStay
			if (!entA->getComponent<Rigidbody>()->isTrigger() && !entB->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onCollisionStay(entB);

				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onCollisionStay(entA);
			}
			else {				
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onTriggerStay(entB);
				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onTriggerStay(entA);
			}
			
		}//primera vez que colisiona
		else {
			if (!entA->getComponent<Rigidbody>()->isTrigger() && !entB->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onCollisionStart(entB);

				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onCollisionStart(entA);
			}
			else {
				for (auto comp = entA->getComponents()->begin(); comp != entA->getComponents()->end(); comp++)
					comp->get()->onTriggerStart(entB);
				for (auto comp = entB->getComponents()->begin(); comp != entB->getComponents()->end(); comp++)
					comp->get()->onTriggerStart(entA);
			}
			_collisions.push_back({ entA,entB });
		}		
	}
	endCollision();
}


bool BulletInstance::find(Entity* entA, Entity* entB)
{
	for (int i = 0; i < _collisions.size(); ++i) {
		if ((entA == _collisions[i].first && entB == _collisions[i].second) || (entB == _collisions[i].first && entA == _collisions[i].second))
			return true;
	}
	return false;
}


void BulletInstance::endCollision()
{
	for (int j = 0; j < _collisions.size(); ++j) {
		bool find_ = false;
		for (int i = 0; i < _dispatcher->getNumManifolds() && !find_; i++)
		{
			// Se consigue de la colision los dos rigidbodys
			btPersistentManifold* contactManifold = _dispatcher->getManifoldByIndexInternal(i);

			// Se cogen los datos del primer rigidbody
			const btCollisionObject* objectA = contactManifold->getBody0();
			const btRigidBody* rigidBodyA = btRigidBody::upcast(objectA);

			// Se cogen los datos del segundo rigidbody
			const btCollisionObject* objectB = contactManifold->getBody1();
			const btRigidBody* rigidBodyB = btRigidBody::upcast(objectB);

			// Cogemos nuestras entidades para decirles lo pertinente 
			Entity* entA = static_cast<Entity*>(rigidBodyA->getUserPointer());
			Entity* entB = static_cast<Entity*>(rigidBodyB->getUserPointer());

			//si ya lo tenemos en nuestro vector de entidades que han colisionado anteriormente dejamos de buscar 
			if ((_collisions[j].first == entA && _collisions[j].second == entB) || (_collisions[j].first == entB && _collisions[j].second == entA))
				find_ = true;
		}
		//vemos si la entidad esta o no en las colisiones de este frame, si no lo esta se avisa que ha acabado la colision
		if (!find_) {
			//si ninguno de los dos cuerpos es trigger
			if (!_collisions[j].first->getComponent<Rigidbody>()->isTrigger() && !_collisions[j].second->getComponent<Rigidbody>()->isTrigger()) {
				for (auto comp = _collisions[j].first->getComponents()->begin(); comp != _collisions[j].first->getComponents()->end(); comp++)
					comp->get()->onCollisionEnd(_collisions[j].second);
				for (auto comp = _collisions[j].second->getComponents()->begin(); comp != _collisions[j].second->getComponents()->end(); comp++)
					comp->get()->onCollisionEnd(_collisions[j].first);
			}
			else {
				for (auto comp = _collisions[j].first->getComponents()->begin(); comp != _collisions[j].first->getComponents()->end(); comp++)
					comp->get()->onTriggerEnd(_collisions[j].second);
				for (auto comp = _collisions[j].second->getComponents()->begin(); comp != _collisions[j].second->getComponents()->end(); comp++)
					comp->get()->onTriggerEnd(_collisions[j].first);
			}
			_collisions.erase(_collisions.begin() + j);
		}
	}
}
