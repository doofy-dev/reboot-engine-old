#include "camera.h"
#include "../component/physics/transform.h"
namespace reboot {
	namespace entity {
		Camera::Camera(driver::PerspectiveCamera *camera, driver::Window *window):GameObject("camera") {
			m_Camera = camera;
			m_Window = window;
			m_Camera->createProjectionMatrix();
		}

		Camera::~Camera() {
		}

		void Camera::update() {
			//m_Camera->createProjectionMatrix();
		}

		maths::mat4 Camera::getViewMatrix() {
		//	std::cout << "camera position: " <<  transform->getPosition()<<std::endl;
			return m_Camera->getViewMatrix(transform->getPosition(), transform->getRotation());
		}
	}
}