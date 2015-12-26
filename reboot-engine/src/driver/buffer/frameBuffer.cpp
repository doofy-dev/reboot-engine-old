#include "frameBuffer.h"

namespace reboot {
	namespace driver {
	
		FrameBuffer::FrameBuffer(unsigned short width, unsigned short height) 
			: m_Width(width), m_Height(height)
		{
			glGenFramebuffers(1, &m_bufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);

			//COLOR BUFFER INITIALIZATION
			glGenTextures(1, &m_ColorTexture);
			glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
			//DEPTH BUFFER INITIALIZATION
			glGenRenderbuffers(1, &m_DepthBuffer);
			glBindRenderbuffer(GL_RENDER, m_DepthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);

			//Final configuration
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorTexture, 0);
			GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
			glDrawBuffers(1, DrawBuffers);
			glBindTexture(GL_TEXTURE_2D, 0);
			//If something happend
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				std::cout << "Framebuffer is failed to initiate!" << std::endl;
				clean();
			}
		}

		FrameBuffer::~FrameBuffer() {
			clean();
		}

		void FrameBuffer::clean() const {
			glDeleteTextures(1, &m_ColorTexture);
			glDeleteBuffers(1, &m_DepthBuffer);
			glDeleteFramebuffers(1, &m_bufferID);
		}

		void FrameBuffer::renderToColorBuffer() {

		}

		void FrameBuffer::renderToDepthBuffer() {

		}

		void FrameBuffer::bind() const {
			glBindFramebuffer(GL_FRAMEBUFFER,m_bufferID);
			glViewport(0, 0, m_Width, m_Height);
		}

		void FrameBuffer::unbind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

	}
}