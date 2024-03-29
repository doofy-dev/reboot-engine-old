#pragma once

#include <GL/glew.h>
#include <vector>
#include "../../math/maths.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
namespace reboot {
	namespace driver {

		class Buffer {

		private:
			GLuint m_BufferID;
			GLuint m_CompoentCount;
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			Buffer(aiVector3D* data, GLsizei count, GLuint componentCount);

			void bind() const;
			void unbind() const;
			
			inline GLuint Buffer::getComponentCount()const { return m_CompoentCount; }
		private:
			void load(GLfloat* data, GLsizei count, GLuint componentCount);
		};

	}
}