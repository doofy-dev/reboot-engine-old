#pragma once

#include "../component.h"
#include "../../math/maths.h"
#include "../../driver/window/window.h"
#include <GLFW/glfw3.h>
namespace reboot {
	namespace component {
		namespace control {
			class FreeMove : public Component{
			private:
				driver::Window *m_Window;
			public :
				FreeMove(driver::Window *window);
				~FreeMove();
				void update();
			private:
				void moveFromLook(float x, float y, float z);
			};
		}
	}
}