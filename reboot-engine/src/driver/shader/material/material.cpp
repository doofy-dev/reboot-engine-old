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

			void Material::addUniform(shader::UniformValue* value) {
				value->connectToShader(shader->getID());
				m_Locations.insert(std::make_pair(value->getName, value));
			}

			shader::UniformValue* Material::getUniform(const GLchar *name) {
				return m_Locations[name];
			}
		}
	}
}