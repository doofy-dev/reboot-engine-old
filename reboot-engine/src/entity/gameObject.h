#pragma once

#include <vector>

namespace reboot {
	namespace component {
		class Component;
		class Transform;
	}
	namespace entity {
		class GameObject {
		private:
			std::vector<component::Component*> components;
			unsigned short m_Layer;
		public:
			component::Transform* transform;
		public:
			GameObject();
			~GameObject();
			void instantinate();
			void addChild(GameObject* children);
			void addCompontent(component::Component* component);

			inline void setLayer(unsigned short layer) { m_Layer = layer; }
			inline unsigned short getLayer() const { return m_Layer; }
			void executeUpdate();
		};
	}
}