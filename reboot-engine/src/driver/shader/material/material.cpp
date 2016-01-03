#include "material.h"

namespace reboot {
	namespace driver {
		namespace shader {

			Material::Material(const char* vertexShader, const char* fragmentShader)
			{
				shader = new Shader(vertexShader, fragmentShader);
			}

			Material::~Material() {
				delete shader;
			}

			void Material::addUniform(shader::UniformValue* value) {
				shader->enable();
				std::cout << "Adding uniform: " << value->getName() << std::endl;
				value->connectToShader(shader->getID());
				m_Uniforms.insert(std::make_pair(value->getName(), value));
				shader->disable();
			}

			shader::UniformValue* Material::getUniform(const GLchar *name) {
				return m_Uniforms[name];
			}


			void Material::addTexture(GLuint location, shader::Texture* texture) {
				m_Texures.insert(std::make_pair(location, texture));
			}


			void Material::load() {
				shader->enable();
				for (auto iter = m_Uniforms.begin(); iter != m_Uniforms.end(); ++iter)
					iter->second->load();

				for (auto iter = m_Texures.begin(); iter != m_Texures.end(); ++iter)
					iter->second->bind(iter->first);
			}

			void Material::unload() {

				for (auto iter = m_Texures.begin(); iter != m_Texures.end(); ++iter)
					iter->second->unbind();
				shader->disable();
			}
		}
	}
}