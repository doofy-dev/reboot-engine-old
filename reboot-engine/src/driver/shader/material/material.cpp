#include "material.h"

namespace reboot {
	namespace driver {
		namespace shader {

			Material::Material(const char* vertexShader, const char* fragmentShader) {
				this->shader = new Shader(vertexShader, fragmentShader);
			}

			Material::~Material() {
				delete shader;
			}

			void Material::addUniform(const GLchar *name) {
				m_Locations.insert(std::make_pair(name, shader->getUniformLocation(name)));
			}

			GLint Material::getUniform(const GLchar *name) {
				return m_Locations[name];
			}
		}
	}
}