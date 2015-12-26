#pragma once

#include <iostream>
#include <GL/glew.h>


namespace reboot {
	namespace driver {
		class FrameBuffer {
		private:
			GLuint m_bufferID;
			GLuint m_ColorTexture;
			GLuint m_DepthTexture;
			GLuint m_DepthBuffer;
			unsigned short m_Width, m_Height;

		public:
			FrameBuffer(unsigned short width, unsigned short height);
			~FrameBuffer();
			void renderToColorBuffer();
			void renderToDepthBuffer();
			void bind() const;
			void unbind() const;
			void clean() const;
			inline GLuint getTextureID() { return m_ColorTexture; }
		};
	}
}