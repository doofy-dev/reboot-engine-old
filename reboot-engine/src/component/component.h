#pragma once

#include <string>

namespace reboot {
	namespace entity {
		class GameObject;
	}
	namespace component {

		class Component {
		private:
			std::string m_Name;
		public:
			entity::GameObject *gameObject;
			Component(std::string name);
			virtual ~Component();
			virtual void update();

			inline std::string& getName() { return m_Name; }
			void assingGameObject(entity::GameObject* GameObject);
		};
	}
}