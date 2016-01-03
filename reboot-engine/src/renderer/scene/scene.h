#pragma once

#include <vector>
#include "../../entity/gameObject.h"

namespace reboot {
	namespace renderer {
		class Scene {

		private:
			std::vector<entity::GameObject> m_GameObjects;
			const char* m_Name;
		public:
			Scene(const char* name);
			~Scene();
			void assingGameObject(entity::GameObject& gameObject);
			void removeGameObject(entity::GameObject* gameObject);
			void callUpdate();
			std::vector<entity::GameObject>& Scene::getObjects() { return m_GameObjects; }
		};
	}
}