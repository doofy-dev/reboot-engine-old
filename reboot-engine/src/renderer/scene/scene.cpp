#include "scene.h"

namespace reboot {
	namespace renderer {
		Scene::Scene(const char* name) {
			m_Name = name;
		}
		
		Scene::~Scene() {
	//		for (unsigned int i = 0; i < m_GameObjects.size(); i++)
//				delete m_GameObjects[i];
		}

		void Scene::assingGameObject(entity::GameObject* gameObject) {
			m_GameObjects.push_back(gameObject);
		}

		void Scene::removeGameObject(entity::GameObject* gameObject) {
		/*	for (unsigned int i = 0; i < m_GameObjects.size(); i++) {
				if (m_GameObjects[i] == gameObject) {
					delete m_GameObjects[i];
					break;
				}
			}*/
		}

		void Scene::callUpdate() {
			for (unsigned int i = 0; i < m_GameObjects.size(); i++)
				m_GameObjects[i]->executeUpdate();
		}
	}
}