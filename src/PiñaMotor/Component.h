#pragma once
#include <map>
#include <string>

class Entity;

//clase abstracta de todos los componentes
class Component {
	friend  Entity;

public:
	virtual ~Component() {};

	virtual bool init(const std::map<std::string, std::string>& mapa) = 0;

	virtual void Start() {} ;

	virtual void OnTriggerStart() {};
	virtual void OnTriggerStay() {};
	virtual void OnTriggerEnd() {};

	virtual void OnCollisionStart() {};
	virtual void OnCollisionStay() {};
	virtual void OnCollisionEnd() {};

	virtual void Update() {};
	virtual void FixedUpdate(){};

	void SetActive(bool toggle) 
	{
		_active = toggle;
	}

	Entity* getEntity() { return _myEntity; }
	//TODO:Como cambiar cosas de un componente a otro, pasando por la entidad
	/*template<typename T>
	T* getComponent() {
		return _myEntity->getComponent<T>();
	}*/

protected:
	virtual void Render() {};
	bool _active = true;
	Entity* _myEntity = nullptr;
};