#include "component.h"
#include "../entity/gameObject.h"
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
			this->gameObject = gameObject;
		}
	}
}