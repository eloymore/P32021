#include "Transform.h"
#include "Entity.h"

Transform::Transform(Vector3<float> position, Vector3<float> rotation, Vector3<float> scale, Transform* parent) :
	_parent(parent), _position(position), _rotation(rotation), _scale(scale) {
	if (parent == nullptr) {
		_localPosition = _position;
		_localRotation = _rotation;
		_localScale = _scale;
		
	}
	else {
		_localPosition = inverseTransformDirection(parent->position());
		_localRotation = inverseTransformDirection(parent->rotation());
		_localScale = inverseTransformDirection(parent->scale());
	}

}

void Transform::translate(float x, float y, float z) {
	_position = { _position.getX() + x,
				  _position.getY() + y,
				  _position.getZ() + z };
	
	_localPosition = { _localPosition.getX() + x,
					   _localPosition.getY() + y, 
					   _localPosition.getZ() + z };
}

void Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo) {
	if (relativeTo == Space::Self) {
		//Cambiamos la rotacion x, y, z angulo
		_rotation = { _rotation.getX() + xAngle,
					  _rotation.getY() + yAngle,
					  _rotation.getZ() + zAngle };

		_localRotation = { _localRotation.getX() + xAngle,
						   _localRotation.getY() + yAngle,
						   _localRotation.getZ() + zAngle };
	}
	//Esto no se si estar� bien porque lo he intentado con quaternion pero no soy capaz
	//en el caso de no funcionar se puede dejar solo la rotacion respecto a si mismo (Self)
	else {
		//Transladamos el obj al centro (guardamos la direccion)
		Vector3<float> dir = _position;
		if (relativeTo == Space::World)
			setPosition(0, 0, 0);
		else
			setPosition(_parent->position());

		//Rotamos x, y, z angulo
		rotate(xAngle, yAngle, zAngle, Space::Self);
		Vector3<float> angleX = { 0, cos(xAngle), sin(xAngle) };
		Vector3<float> angleY = { sin(yAngle), 0, cos(yAngle) };
		Vector3<float> angleZ = { sin(zAngle), cos(zAngle), 0 };
		Vector3<float> newDir = dir + angleX + angleY + angleZ;

		//Volvemos a transladar el obj habiendo rotado tb la direccion
		setPosition(newDir);
	}
}

Transform* Transform::findChild(char* name) {
	for (auto c : _vChild) {
		if (c->getEntity()->getName() == name)
			return c;
	}
	return nullptr;
}

void Transform::setPosition(Vector3<float> v) {
	_position = v;
	_localPosition = inverseTransformDirection(v);
}

void Transform::setPosition(float x, float y, float z) {
	_position = { x, y, z };
	_localPosition = inverseTransformDirection(x, y, z);
}

void Transform::setRotation(Vector3<float> v) {
	_rotation = v;
	_localRotation = inverseTransformDirection(v);
}

void Transform::setRotation(float x, float y, float z) {
	_rotation = { x, y, z };
	_localRotation = inverseTransformDirection(x, y, z);
}

void Transform::setScale(Vector3<float> v)
{
	_scale = v;
	_localScale = inverseTransformDirection(v);
}

void Transform::setScale(float x, float y, float z)
{
	_scale = { x, y, z };
	_localScale = inverseTransformDirection(x, y, z);
}

void Transform::setLocalPosition(Vector3<float> v)
{
	_localPosition = v;
	_position = transformDirection(v);
}

void Transform::setLocalPosition(float x, float y, float z)
{
	_localPosition = { x, y, z };
	_position = transformDirection(x, y, z);
}

void Transform::setLocalRotation(Vector3<float> v)
{
	_localRotation = v;
	_rotation = transformDirection(v);
}

void Transform::setLocalRotation(float x, float y, float z)
{
	_localRotation = { x, y, z };
	_rotation = transformDirection(x, y, z);
}

void Transform::setLocalScale(Vector3<float> v)
{
	_localScale = v;
	_scale = transformDirection(v);
}

void Transform::setLocalScale(float x, float y, float z)
{
	_localScale = { x, y, z };
	_scale = transformDirection(x, y, z);
}

Vector3<float> Transform::transformDirection(Vector3<float> direction) {
	return { abs(direction.getX() + _parent->localPosition().getX()),
			 abs(direction.getY() + _parent->localPosition().getY()),
			 abs(direction.getZ() + _parent->localPosition().getZ()) };
}

Vector3<float> Transform::transformDirection(float x, float y, float z) {
	return { abs(x + _parent->localPosition().getX()),
			 abs(y + _parent->localPosition().getY()),
			 abs(z + _parent->localPosition().getZ()) };
}

Vector3<float> Transform::inverseTransformDirection(Vector3<float> direction) {
	return { abs(direction.getX() - _parent->localPosition().getX()),
			 abs(direction.getY() - _parent->localPosition().getY()),
			 abs(direction.getZ() - _parent->localPosition().getZ()) };
}

Vector3<float> Transform::inverseTransformDirection(float x, float y, float z) {
	return { abs(x - _parent->localPosition().getX()),
			 abs(y - _parent->localPosition().getY()),
			 abs(z - _parent->localPosition().getZ()) };
}
