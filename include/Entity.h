#pragma once
#include "Component.h"
#include "ecs.h"
#include "ComponentFactory.h"
#include <map>
#include "Vector3.h"
#include "Quaternion.h"

class Entity {
public:
	Entity();
	Entity(std::string entityName, int id, std::string entityTag = "Default");

	~Entity();

	Component* addComponent(const std::string& compName, const std::map<std::string, std::string>& map) {
		Component* t = ComponentFactory::getInstance().getComponent(compName);
		if (t != nullptr) {
			t->_myEntity = this;//ponemos la entidad en el componente
			std::unique_ptr<Component> upt(t);
			compUnique.push_back(std::move(upt));
			compMaps.push_back(map);
			compinits.push_back(false);

			return t;
		}
		throw std::exception("Error de carga del componente ");
	}

	/// <summary>
	/// Devuelve un componente de la entidad, o nullptr si no lo tiene. Coste: O(N) :(
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename T>
	T* getComponent() {
		T* ret = nullptr;
		int i = 0;
		while (i < compUnique.size() && ret == nullptr) {
			ret = dynamic_cast<T*>(compUnique[i].get());
			++i;
		}

		return ret;
	}

	/// <summary>
	/// Devuelve si tiene o no un componente. Coste: O(N) :(
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename T>
	bool hasComponent() {
		return getComponent<T>() != nullptr;
	}

	const std::string getName() { return _name; }
	const std::string getTag() { return _tag; }
	const bool isPaused() { return _paused; }

	void setPaused(bool paused) { _paused = paused; }

	int getId() { return _id; }

	bool init();

	void update();

	void fixedUpdate();

	void render();

	std::vector<std::unique_ptr<Component>>* getComponents() { return &compUnique; }
	
	static Entity* instantiate(std::string file, Vector3<> position = Vector3<>::zero(), Quaternion rotation = Quaternion());

private:
	std::string _name;

	int _id;
	//si la entidad esta pausada
	bool _paused;

	std::string _tag;

	//aqui estaran los componentes de esta entidad
	std::vector<std::unique_ptr<Component>> compUnique;

	std::vector<std::map<std::string, std::string>> compMaps;

	std::vector<bool> compinits;

	bool _needsOtherEntity;

	//numero de veces que puedes intentar iniciar tus componentes (para evitar bucle infinito)
	int _numTriesToLoad;
};