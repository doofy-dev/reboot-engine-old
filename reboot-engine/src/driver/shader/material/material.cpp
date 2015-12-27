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
				m_Uniforms.insert(std::make_pair(value->getName(), value));
			}

			shader::UniformValue* Material::getUniform(const GLchar *name) {
				return m_Uniforms[name];
			}

			void Material::load() {
				for (auto iter = m_Uniforms.begin(); iter != m_Uniforms.end(); ++iter)
					iter->second->load();
			}
		}
	}
}