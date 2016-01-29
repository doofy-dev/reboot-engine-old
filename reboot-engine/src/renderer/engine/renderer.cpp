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
#define withCamera
		void Renderer::render(entity::Camera &camera) {
			std::vector<entity::GameObject*> gameObjects = m_Scene->getObjects();
			m_Window->clear();
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
#ifdef withCamera
			maths::mat4 view = camera.getViewMatrix();
			maths::mat4 projection = camera.getCamera()->getProjectionMatrix();
#endif
			for (unsigned int i = 0; i < gameObjects.size(); i++) {
				entity::GameObject* object = gameObjects[i];
				object->executeUpdate();
				if (object->getRenderable() == nullptr)
					continue;
		//		std::cout << "Rendering : " << object->getName() << std::endl;
				component::Renderable* renderable = object->getRenderable();
			//	std::cout << "View: " << *view << std::endl;
			//	std::cout << "Proj: " << *projection << std::endl;
				renderable->bind();

#ifdef withCamera
				renderable->getMaterial()->shader->loadUniformMat4f("mvp.view", view);
				renderable->getMaterial()->shader->loadUniformMat4f("mvp.projection", projection);
#endif
				glDrawElements(renderable->getRendeMode(),
					renderable->getIBO()->getCount(), GL_UNSIGNED_INT, 0);
				
				renderable->unbind();
			}

		}

		void Renderer::flush() {
			m_Window->update();
		}
	}
}