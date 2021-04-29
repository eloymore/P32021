#pragma once
#include "ComponentFactory.h"
#include "ecs.h"
/// <summary>
/// clase para registrar los nuevos componentes
/// forma de uso:						donde Transform es el nombre del componente a a�adir
/// ComponentFactoryRegistrations::ComponentFactoryRegistration<Transform> cpm;
/// </summary>
namespace ComponentFactoryRegistrations {
	template<typename T> class ComponentFactoryRegistration {
	public:
		ComponentFactoryRegistration(std::string compName) {
			ComponentFactory::getInstance().registerGenerator(indexOf<T,ComponentsList>, compName, []()
				{
					return static_cast<Component*>(new T());
				}
			);
		}
	};
}