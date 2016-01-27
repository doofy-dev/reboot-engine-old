#include "component.h"
#include "../entity/gameObject.h"
#include "physics/transform.h"
namespace reboot {
	namespace component {
		Component::Component(std::string name) {
			gameObject = nullptr;
			m_Name = name;
		}

		Component::~Component(){
		
		}

		void Component::update() {}

		void Component::assingGameObject(entity::GameObject* gameObject) {
			std::cout << "Assigning "<<getName()<<" to gameObject: " << gameObject->getName() << std::endl;
			this->gameObject = gameObject;
		}
	}
}