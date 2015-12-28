#include "renderer.h"

namespace reboot {
	namespace renderer {
		Renderer::Renderer(Scene* scene, driver::Window* window) {
			m_Scene = scene;
			m_Window = window;
		}

		Renderer::~Renderer() {
			delete m_Scene;
		}

		void Renderer::render() {
			std::vector<entity::GameObject*> gameObjects = m_Scene->getObjects();
			m_Window->clear();

		}

		void Renderer::flush() {

			m_Window->update();
		}
	}
}