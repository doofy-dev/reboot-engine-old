#include "component.h"
#include "../entity/gameObject.h"
namespace reboot {
	namespace component {
		Component::Component() {
			gameObject = &entity::GameObject();
		}

		Component::~Component(){
		
		}

		void Component::update() {}

		void Component::assingGameObject(entity::GameObject* gameObject) {
			this->gameObject = gameObject;
		}
	}
}