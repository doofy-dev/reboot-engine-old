#include "gameObject.h"

#include "../component/component.h"
#include "../component/physics/transform.h"

namespace reboot {
	namespace entity {
		GameObject::GameObject() {
			transform = &component::Transform();
			transform->assingGameObject(this);
		}

		GameObject::~GameObject() {
			delete transform;
			for (unsigned int i = 0; i < components.size(); i++) {
				delete &components[i];
			}
			
		}

		void GameObject::instantinate() {

		}

		void GameObject::addChild(GameObject* child) {
			child->transform->setParent(this);
			transform->childrens.push_back(child);
		}

		void GameObject::addCompontent(component::Component* component) {
			component->assingGameObject(this);
			components.push_back(component);
		}

		void GameObject::executeUpdate() {

		}

	}
}