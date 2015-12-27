#pragma once

#include <vector>

namespace reboot {
	namespace component {
		class Component;
		class Transform;
		class Renderable;
	}
	namespace entity {
		class GameObject {
		private:
			std::string m_Name;
			std::vector<component::Component*> components;
			unsigned short m_Layer;
			component::Renderable* m_Renderable;

		public:
			component::Transform* transform;
		public:
			GameObject(std::string name);
			~GameObject();

			virtual void instantinate();
			void addChild(GameObject* children);
			void addCompontent(component::Component* component);
			void addCompontent(component::Renderable* component);

			component::Component* getComponent(std::string name);
			inline void setLayer(unsigned short layer) { m_Layer = layer; }
			inline unsigned short getLayer() const { return m_Layer; }
			
			//@TODO: getRenderer, clone, remove, init

			inline component::Renderable* GameObject::getRenderable() {
				return m_Renderable;
			}

			void executeUpdate();
			virtual GameObject* clone() { return new GameObject(*this); }
		};
	}
}