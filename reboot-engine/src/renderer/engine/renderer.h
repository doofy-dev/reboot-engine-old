#pragma once

#include <vector>
#include <GL/glew.h>
#include "../../driver/window/window.h"
#include "../../entity/camera.h"

namespace reboot {
	namespace renderer {
		class Scene;
		class Renderer {
		
		private:
			renderer::Scene* m_Scene;
			driver::Window* m_Window;
		public:
			Renderer(renderer::Scene *scene, driver::Window *window);
			~Renderer();

			void render(entity::Camera &camera);
			void flush();
		};
	}
}