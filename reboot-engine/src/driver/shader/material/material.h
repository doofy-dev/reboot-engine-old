#pragma once

#include <GL/glew.h>
#include "../shader.h"
#include <map>

namespace reboot {
	namespace driver {
		namespace shader {
			class Material{
			public:
				Shader* shader;
			private:
				std::map<const GLchar*, GLint> m_Locations;
			public:
				Material(const char* vertexShader, const char* fragmentShader);
				~Material();

				void addUniform(const GLchar *name);
				GLint getUniform(const GLchar* name);
			};
		}
	}
}