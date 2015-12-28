#pragma once

#include <vector>
#include <GL/glew.h>
#include "../../driver/window/window.h"
#include "../scene/scene.h"

namespace reboot {
	namespace renderer {
		class Renderer {
		
		private:
			Scene* m_Scene;
			driver::Window* m_Window;
		public:
			Renderer(Scene * scene, driver::Window* window);
			~Renderer();

			void render();
			void flush();
		};
	}
}