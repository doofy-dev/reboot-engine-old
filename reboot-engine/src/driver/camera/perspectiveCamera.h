#pragma once
#include <GL/glew.h>
#include "../../math/maths.h"

namespace reboot {
	namespace driver {
		class PerspectiveCamera {
		private:
			int m_FrameWidth, m_FrameHeight;
			int m_RenderLayer;
			float m_FieldOfView;
			float m_NearPlane;
			float m_FarPlane;
			maths::mat4 m_ProjectionMatrix;
			maths::vec3 m_BackgroundColor;

		public:
			PerspectiveCamera(int width, int height);
			~PerspectiveCamera();
			maths::mat4 getViewMatrix(maths::vec3& position, maths::vec3& rotation);
			void createProjectionMatrix();

			const void enableCulling();
			const void disableCulling();
			const void enableBlend();
			const void disableBlend();

			inline maths::mat4 getProjectionMatrix() { return m_ProjectionMatrix; }
			inline void setFrameSize(const int frameWidth, const int frameHeight) {
				m_FrameHeight = frameHeight;
				m_FrameWidth = frameWidth;
			}
			inline maths::vec3 getBackgroundColor() { return m_BackgroundColor; }
			inline void setBackgroundColor(maths::vec3 color) { m_BackgroundColor = color; }
		};
	}
}