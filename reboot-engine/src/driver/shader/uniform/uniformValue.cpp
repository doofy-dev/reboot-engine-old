#include "uniformValue.h"

namespace reboot{
	namespace driver {
		namespace shader {
			UniformValue::UniformValue(const GLchar* name, GLuint shaderID) 
			:m_Name(name){
			}

			UniformValue::~UniformValue() {
			}

			void UniformValue::load(GLint location, float value) {
				glUniform1f(location, value);
			}

			void UniformValue::load(GLint location, int value) {
				glUniform1i(location, value);
			}

			void UniformValue::load(GLint location, const vec2& value) {
				glUniform2f(location, value.x, value.y);
			}

			void UniformValue::load(GLint location, const vec3& value) {
				glUniform3f(location, value.x, value.y, value.z);
			}

			void UniformValue::load(GLint location, const vec4& value) {
				//std::cout << "loading " << m_Name << " in " << m_Location << " or "<<location << std::endl;
				glUniform4f(location, value.x, value.y, value.z, value.w);
			}

			void UniformValue::load(GLint location, const mat4& uniform) {
				float data[16];
				uniform.getArray(data);
				glUniformMatrix4fv(location, 1, GL_FALSE, data);
			}

			void UniformValue::connectToShader(GLuint shaderID) {
				m_Location = glGetUniformLocation(shaderID, m_Name);
				
				std::cout << "Setting " << m_Name << " in Shader(" << shaderID << ") location("<<m_Location << ")" << std::endl;

//				GLint result;
			//	glGetShaderiv(shaderID, GL_GET_UNI, &result);

			}

			void UniformValue::load(){}
		}
	}
}