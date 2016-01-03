#include "renderer.h"
#include "../../component/renderable/Renderable.h"

#include "../scene/scene.h"
namespace reboot {
	namespace renderer {
		Renderer::Renderer(renderer::Scene* scene, driver::Window* window) {
			m_Scene = scene;
			m_Window = window;
		}

		Renderer::~Renderer() {
			delete m_Scene;
		}

		void Renderer::render() {
			std::vector<entity::GameObject> gameObjects = m_Scene->getObjects();
			m_Window->clear();
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			for (unsigned int i = 0; i < gameObjects.size(); i++) {
				entity::GameObject object = gameObjects[i];
				if (object.getRenderable() == nullptr)
					continue;
		//		std::cout << "Rendering : " << object->getName() << std::endl;
				component::Renderable* renderable = object.getRenderable();
				renderable->bind();
				glDrawElements(renderable->getRendeMode(),
					renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);
				
				renderable->unbind();
			}

		}

		void Renderer::flush() {
			m_Window->update();
		}
	}
}