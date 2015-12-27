#pragma once

#include <GL/glew.h>
#include "../shader.h"
#include "../uniform/uniformValue.h"
#include <map>

namespace reboot {
	namespace driver {
		namespace shader {
			class Material{
			public:
				Shader* shader;
			private:
				std::map<const GLchar*, shader::UniformValue*> m_Locations;
			public:
				Material(const char* vertexShader, const char* fragmentShader);
				~Material();

				void addUniform(shader::UniformValue* value);
				shader::UniformValue* getUniform(const GLchar* name);

				void load();
			};
		}
	}
}