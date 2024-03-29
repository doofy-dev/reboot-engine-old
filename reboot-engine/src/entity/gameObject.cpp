#include "gameObject.h"

#include "../component/component.h"
#include "../component/physics/transform.h"

namespace reboot {
	namespace entity {
		GameObject::GameObject(std::string name)
		:m_Name(name), m_Layer(0){
			m_Renderable = nullptr;
			transform = new component::Transform();
			transform->assingGameObject(this);
		}

		GameObject::~GameObject() {
		//	for (unsigned int i = 0; i < transform->childrens.size(); i++)
		//		delete transform->childrens[i];
		//	delete transform;
		//	delete m_Renderable;
	/*		for (unsigned int i = 0; i < components.size(); i++) {
				delete &components[i];
			}*/
		}

		void GameObject::instantinate(renderer::Scene* scene) {
			scene->assingGameObject(this);
			for (int i = 0; i < transform->childrens.size(); i++)
				transform->childrens[i]->instantinate(scene);
		}
		void GameObject::update() {}

		void GameObject::addChild(GameObject* child) {
			transform->addChild(child);
		}

		void GameObject::addCompontent(component::Component* component) {
			component->assingGameObject(this);
			components.push_back(component);
		}

		void GameObject::addCompontent(component::Renderable* component) {
			component->assingGameObject(this);
			m_Renderable = component;
		}

		void GameObject::executeUpdate() {
			update();
			for (unsigned int i = 0; i < components.size(); i++)
				components[i]->update();
			for (unsigned int i = 0; i < transform->childrens.size(); i++)
				transform->childrens[i]->executeUpdate();
		}

		component::Component* GameObject::getComponent(std::string name) {
			for (unsigned int i = 0; i < components.size(); i++) {
				if (components[i]->getName() == name) {
					return components[i];
				}
			}
			return nullptr;
		}
	}
}