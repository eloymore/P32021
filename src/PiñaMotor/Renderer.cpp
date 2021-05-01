#include "Renderer.h"
#include "OgreSceneManager.h"
#include "OgreMesh.h"
#include "OgreEntity.h"
#include "OgreMotor.h"
#include "Entity.h"
#include "Transform.h"
#include "Rigidbody.h"

bool Renderer::init(const std::map<std::string, std::string>& mapa){
	//_mesh=map.mesh;
	//_material=map.material;
	//_ogreNode = OgreInstance::getInstance()->getmSM()->getRootSceneNode()->createChildSceneNode("nombredel nodo");
	//_ogreEntity = _ogreEntity->createEntity(_mesh);
	// _ogreNode.attachedObject(_ogreEntity);
	//if(_material!="")
	//_ogreEntity.setMaterialName(_material)
	Transform* _trans = _myEntity->getComponent<Transform>();
	if (name == 0 || name >=3) {
		_ogreEntity = OgreMotor::GetInstance()->getSceneManager()->createEntity("cube.mesh");
		_ogreNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("nSimbad" + name);
		name++;
		_ogreNode->attachObject(_ogreEntity);
		_ogreNode->setScale(_trans->scale());
		_ogreNode->setPosition(_trans->position());
	}
	else  if (name==1){
		_ogreEntity = OgreMotor::GetInstance()->getSceneManager()->createEntity("sphere.mesh");
		_ogreNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("nSimbad" + to_string(name));
		name++;
		_ogreNode->attachObject(_ogreEntity);
		_ogreNode->setScale(_trans->scale());
		_ogreNode->setPosition(_trans->position());
	}
	else {
		_ogreEntity = OgreMotor::GetInstance()->getSceneManager()->createEntity("Sinbad.mesh");
		_ogreNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("nSimbad" + to_string(name));
		name++;
		_ogreNode->attachObject(_ogreEntity);
		_ogreNode->setScale(_trans->scale());
		_ogreNode->setPosition(_trans->position());
	}
	return true;
}
void Renderer::setVisible(bool visible) {
	_visible = visible;
	_ogreNode->setVisible(visible);
}

bool Renderer::isVisible() {
	return _visible;
}

 void Renderer::setMaterial(std::string name) {
	_material = name;
	_ogreEntity->setMaterialName(name);
}

const std::string Renderer::getMaterialName() {
	return _material;
}

const std::string Renderer::getMeshName() {
	return _meshName;	
}

const Ogre::MeshPtr Renderer::getMesh() {
	return _ogreEntity->getMesh();
}

Ogre::SceneNode* Renderer::getNode() const {
	return _ogreNode;
}

void Renderer::setMesh(std::string name) {
	_ogreEntity = _ogreNode->getCreator()->createEntity(name);
	_meshName = name;
}

void Renderer::setMesh(Ogre::MeshPtr mesh) {
	_ogreEntity = _ogreNode->getCreator()->createEntity(mesh);
}

void Renderer::render() {
	if (_visible) {


		/*if (_myEntity->hasComponent<Rigidbody>()) {
			Rigidbody* tr = _myEntity->getComponent<Rigidbody>();
			_ogreNode->setPosition(tr->getbT()->getWorldTransform().getOrigin().getX(), tr->getbT()->getWorldTransform().getOrigin().getY(), tr->getbT()->getWorldTransform().getOrigin().getZ());
			//_ogreNode->setScale(tr->getbT()->sc);
			_ogreNode->setOrientation(tr->getbT()->getOrientation().getW(), tr->getbT()->getOrientation().getX(), tr->getbT()->getOrientation().getY(), tr->getbT()->getOrientation().getZ());
		}

		else*/ if (_myEntity->hasComponent<Transform>()) {
			Transform* tr = _myEntity->getComponent<Transform>();
			_ogreNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
			_ogreNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
			_ogreNode->setOrientation(tr->rotation());
		}
	}
}




