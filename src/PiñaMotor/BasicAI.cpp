#include "BasicAI.h"
#include "Entity.h"

bool BasicAI::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("step") == mapa.end() || mapa.find("threshold") == mapa.end() || mapa.find("thresholdRot") == mapa.end() || mapa.find("stepRot") == mapa.end()) return false;

	_transform = getEntity()->getComponent<Transform>();

	_rigidbody = getEntity()->getComponent<Rigidbody>();

	_moveFlag = _rotFlag = false;

	std::string s = mapa.at("threshold");
	_threshold = std::stof(s);

	s = mapa.at("thresholdRot");
	_thresholdRot = std::stof(s);

	s = mapa.at("stepRot");
	_velRotation = std::stof(s);

	s = mapa.at("step");
	_step = std::stof(s);

	return true;
}

void BasicAI::fixedUpdate() {
	// Movimiento
	if (_moveFlag) { 
		if ((_posObjetivo - _transform->position()).magnitude() < _threshold) {
			_moveFlag = false;
			_rigidbody->setLinearVelocity(Vector3<>(0, 0, 0)); 
		}
		else {
			Vector3<> direction = (_posObjetivo - _transform->position()).normalized();
			direction *= _step;
			_rigidbody->addForce(direction, Vector3<>(0, 0, 0));
		}
	}
	// Rotaci�n
	if (_rotFlag) {

		if (_t>=1) {
			_rotFlag = false;
			_t = 0;
			 btTransform trans;
			 _rigidbody->getbT()->getMotionState()->getWorldTransform(trans);
			 _rotIni = { trans.getRotation() };
		}
		else {
			btTransform trans;
			_t += _velRotation;
			_rigidbody->setRotation(Quaternion::Slerp(Quaternion::Euler(_rotObjetivo), _rotIni,_t, _threshold));
			_rigidbody->getbT()->getMotionState()->getWorldTransform(trans);
			btQuaternion orientation = trans.getRotation();
		}
	}
}

void BasicAI::MoveTo(Vector3<> obj) {
	_posObjetivo = obj;
	_moveFlag = true;
}

void BasicAI::RotateTo(Vector3<> obj) {
	_rotObjetivo = obj;
	_rotFlag = true;
}