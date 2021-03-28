#pragma once
#include "ComponentFactoryRegistration.h"

class Component {
public:
	virtual bool OnTriggerStart() = 0;
	virtual bool OnTriggerStay() = 0;
	virtual bool OnTriggerEnd() = 0;

	virtual bool OnCollisionStart() = 0;
	virtual bool OnCollisionStay() = 0;
	virtual bool OnCollisionEnd() = 0;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;

private:
	virtual void Render() = 0;
};