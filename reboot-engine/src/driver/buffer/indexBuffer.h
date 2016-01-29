#pragma once

#include <GL/glew.h>

namespace reboot {
	namespace driver {

		class IndexBuffer {

		private:
			GLuint m_BufferID;
			GLuint m_Count;
			GLuint* m_Data;
		public:
			IndexBuffer(GLuint* data, GLsizei count);

			void bind() const;
			void unbind() const;

			inline GLuint IndexBuffer::getCount()const { return m_Count; }
			inline GLuint* IndexBuffer::getData()const { return m_Data; }
		};

	}
}