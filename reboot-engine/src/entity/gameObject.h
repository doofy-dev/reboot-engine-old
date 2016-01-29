#pragma once

#include <vector>
#include "../component/renderable/Renderable.h"
#include "../renderer/scene/scene.h"

namespace reboot {
	namespace component {
		class Component;
		class Transform;
	}
	namespace renderer {
		class Scene;
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

			virtual void instantinate(renderer::Scene *scene);
			virtual void update();

			void addChild(GameObject* children);
			void addCompontent(component::Component* component);
			void addCompontent(component::Renderable* component);

			std::string GameObject::getName() { return m_Name; }

			component::Component* getComponent(std::string name);
			inline void setLayer(unsigned short layer) { m_Layer = layer; }
			inline unsigned short getLayer() const { return m_Layer; }
			
			//@TODO: remove

			inline component::Renderable* GameObject::getRenderable() {
				return m_Renderable;
			}

			void executeUpdate();
			virtual GameObject* clone() { return new GameObject(*this); }
		};
	}
}