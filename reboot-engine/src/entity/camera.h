#pragma once
#include "gameObject.h"
#include "../driver/camera/perspectiveCamera.h"
#include "../driver/window/window.h"

namespace reboot {
	namespace entity {
		class Camera : public GameObject {
		private:
			driver::PerspectiveCamera *m_Camera;
			driver::Window *m_Window;
		public:
			Camera(driver::PerspectiveCamera *camera, driver::Window *window);
			~Camera();
			inline driver::PerspectiveCamera *getCamera() { return m_Camera; }
			maths::mat4 getViewMatrix();
			void update();
		};
	}
}