#pragma once
#include "Vector3.h"

class Quaternion {
public:
	float s;
	Vector3<float> v;

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float scalar, Vector3<float>& vector);
	Quaternion(const Quaternion& quat);
	~Quaternion() {};

	static Quaternion Euler(Vector3<float> vector);
	static float Angle(Quaternion& a, Quaternion& b);
	
	float magnitude();
	Quaternion normalize();
	Quaternion conjugate();
	Quaternion inverse();
	Vector3<float> toEuler();
	Ogre::Matrix3 toMatrix();

	Quaternion& operator=(const Quaternion& quat);
	void operator+=(const Quaternion& quat);
	Quaternion operator+(const Quaternion& quat) const;
	void operator-=(const Quaternion& quat);
	Quaternion operator-(const Quaternion& quat) const;
	void operator*=(const Quaternion& quat);
	Quaternion operator*(const Quaternion& quat) const;
	void operator*=(const float value);
	Quaternion operator*(const float value) const;

	operator Ogre::Quaternion() const;
	
};

