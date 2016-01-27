#include "perspectiveCamera.h"

namespace reboot {
	namespace driver {
		PerspectiveCamera::PerspectiveCamera(int width, int height)
			:m_BackgroundColor(maths::vec3(0, 0, 0)), m_NearPlane(0.1f), m_FarPlane(30000), m_RenderLayer(0),
			m_FieldOfView(90)
		{
			m_FrameWidth = width;
			m_FrameHeight = height;
			createProjectionMatrix();
		}
	
		PerspectiveCamera::~PerspectiveCamera(){
		}

		maths::mat4 PerspectiveCamera::getViewMatrix(maths::vec3& position, maths::vec3& rotation) {
			maths::mat4 viewMatrix  = 
				maths::mat4::rotation(rotation.x, maths::vec3(1, 0, 0)) *
				maths::mat4::rotation(rotation.y, maths::vec3(0, 1, 0)) *
				maths::mat4::rotation(rotation.z, maths::vec3(0, 0, 1));
			maths::vec3 negative(-position.x, -position.y, -position.z);
			viewMatrix *= maths::mat4::translation(negative);
			return viewMatrix;
		}

		void PerspectiveCamera::createProjectionMatrix() {
			float aspectRatio = (float)m_FrameWidth / (float)m_FrameHeight;
			m_ProjectionMatrix = maths::mat4::perspective(m_FieldOfView, aspectRatio, m_NearPlane, m_FarPlane);
		}

		const void PerspectiveCamera::enableCulling() {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		const void PerspectiveCamera::disableCulling() {
			glDisable(GL_CULL_FACE);
		}

		const void PerspectiveCamera::enableBlend() {
			glEnable(GL_BLEND);
		}

		const void PerspectiveCamera::disableBlend() {
			glDisable(GL_BLEND);
		}

	}
}