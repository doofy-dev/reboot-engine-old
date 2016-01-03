#pragma once

#include <GL/glew.h>
#include "../uniform/uniformValue.h"
#include "../shader.h"
#include "../texture/texture.h"
#include <map>

namespace reboot {
	namespace driver {
		namespace shader {

			class Material{
			public:
				Shader* shader;
			private:
				std::map<const GLchar*, shader::UniformValue*> m_Uniforms;
				std::map<GLuint, shader::Texture*> m_Texures;
			public:
				Material(const char* vertexShader, const char* fragmentShader);
				~Material();

				void addUniform(shader::UniformValue* value);
				void addTexture(GLuint location, shader::Texture* texture);
				shader::UniformValue* getUniform(const GLchar* name);

				void load();
				void unload();
			};
		}
	}
}