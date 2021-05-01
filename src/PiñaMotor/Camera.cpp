#include "Camera.h"
#include "OgreMotor.h"
#include <OgreNode.h>
#include "Transform.h"
#include "Entity.h"
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

Camera::Camera() {

}

bool Camera::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("near") == mapa.end() || mapa.find("far") == mapa.end() || mapa.find("autoaspect") == mapa.end() || mapa.find("aspect") == mapa.end() ||
		mapa.find("fov") == mapa.end() || mapa.find("proyection") == mapa.end() || mapa.find("viewport") == mapa.end() || mapa.find("color") == mapa.end()) return false;
	
	_cam = OgreMotor::GetInstance()->getSceneManager()->createCamera(_myEntity->getName());
	_camNode = OgreMotor::GetInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(_myEntity->getName());
	_viewport = OgreMotor::GetInstance()->getRenderWindow()->addViewport(_cam);
	_camNode->attachObject(_cam);	

	std::string s = mapa.at("near");
	setNearClipPlane(std::stof(s));

	s = mapa.at("far");
	setFarClipPlane(std::stof(s));

	bool b;
	s = mapa.at("autoaspect");
	if (s == "true") b = true;
	else if (s == "false") b = false;
	else return false;

	s = mapa.at("aspect");
	setAspectRatio(b, std::stof(s));

	s = mapa.at("fov");
	setFOVY(std::stof(s));

	s = mapa.at("proyection");
	setProjectionType((Camera::ProjectionType)(std::stoi(s)));

	s = mapa.at("viewport");
	std::string x = s.substr(0, s.find(","));
	std::string y = s.substr(x.length() + 1, s.find(","));
	std::string z = s.substr(y.length() + x.length() + 2, s.find(","));
	std::string w = s.substr(z.length() + y.length() + x.length() + 3, s.find(","));
	setViewport(Vector2<>(std::stof(x), std::stof(y)), Vector2<>(std::stof(z), std::stof(w)));

	s = mapa.at("color");
	x = s.substr(0, s.find(","));
	y = s.substr(x.length() + 1, s.find(","));
	z = s.substr(y.length() + x.length() + 2, s.find(","));
	setBackgroundColor(std::stof(x), std::stof(y), std::stof(z));

	return true;
}

Camera::ProjectionType Camera::getProjectionType() {
	return (Camera::ProjectionType)_cam->getProjectionType();
}

void Camera::setAspectRatio(bool autoAspectRatio, float aspectRatio) {
	if (!autoAspectRatio) {
		_cam->setAspectRatio(aspectRatio);
	}
	else {
		_cam->setAutoAspectRatio(autoAspectRatio);
	}
}

void Camera::setFOVY(float fov) {
	_cam->setFOVy(Ogre::Radian(fov));
}

void Camera::setProjectionType(Camera::ProjectionType type) {
	_cam->setProjectionType((Ogre::ProjectionType)type);
}

void Camera::setViewport(Vector2<> pos, Vector2<> size) {
	_viewport->setDimensions(pos.x, pos.y, size.x, size.y);
}

void Camera::setBackgroundColor(Vector3<> color) {
	_viewport->setBackgroundColour(Ogre::ColourValue(color.x, color.y, color.z));
}

void Camera::setBackgroundColor(float r, float g, float b) {
	setBackgroundColor({ r, g, b });
}

void Camera::render() {
	Transform* tr;
	if ((tr = _myEntity->getComponent<Transform>()) != nullptr) {
		_camNode->setPosition(tr->position().x, tr->position().y, tr->position().z);
		_camNode->setScale(tr->scale().x, tr->scale().y, tr->scale().z);
		_camNode->setOrientation(tr->rotation());
	}
}
