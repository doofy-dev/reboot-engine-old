#include "shader.h"
#include <GL/glew.h>
namespace reboot {
	namespace driver {
		Shader::Shader(const char *vertPath, const char *fragPath) {
			m_VertPath = vertPath;
			m_FragPath = fragPath;

			m_ShaderID = load();
			std::cout << "Shader created with ID: " << m_ShaderID << std::endl;
			if (m_ShaderID == 0) {
				std::cout << "Deleting shader because of errors!" << std::endl;
				glDeleteProgram(m_ShaderID);
			}

			GLint numActiveAttribs = 0;
			GLint numActiveUniforms = 0;
			glGetProgramiv(m_ShaderID, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
			glGetProgramiv(m_ShaderID, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

			for (int unif = 0; unif < numActiveUniforms; ++unif)
			{

				std::vector<GLchar> nameData(256);
				GLint arraySize = 0;
				GLenum type = 0;
				GLsizei actualLength = 0;
				glGetActiveUniform(m_ShaderID, unif, nameData.size(), &actualLength, &arraySize, &type, &nameData[0]);
				std::string name((char*)&nameData[0], actualLength - 1);
				for (unsigned int i = 0; i < 255; i++) {
					std::cout << nameData[i];
				}
				std::cout << std::endl;
				nameData.clear();
			}
			
		}

		Shader::~Shader() {
			std::cout << "Deleting shader(" << m_ShaderID << ")" << std::endl;
			glDeleteProgram(m_ShaderID);
		}

		void Shader::enable() const {
		//	std::cout << "Enabling shader(" << m_ShaderID << ")" << std::endl;
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const {
			glUseProgram(0);
		}

		GLint Shader::getUniformLocation(const GLchar *name) {
			return glGetUniformLocation(m_ShaderID,name);
		}

		void Shader::loadUniform1f(const GLchar *name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::loadUniform1i(const GLchar *name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::loadUniform2f(const GLchar *name, const vec2& value) {
			glUniform2f(getUniformLocation(name), value.x, value.y);
		}

		void Shader::loadUniform3f(const GLchar *name, const vec3& value) {
			glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
		}

		void Shader::loadUniform4f(const GLchar *name, const vec4& value) {
			glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
		}

		void Shader::loadUniformMat4f(const GLchar *name, const mat4& uniform) {
			float data[16];
			uniform.getArray(data);
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, data);
		}

		GLuint Shader::load() {
			GLuint program = glCreateProgram();

			GLuint fragment = buildShader(m_FragPath, GL_FRAGMENT_SHADER);
			GLuint vertex = buildShader(m_VertPath,GL_VERTEX_SHADER);
			if (fragment == 0 || vertex == 0) {
				std::cout << "Shader creation failed!" << std::endl;
				return 0;
			}
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return program;
		}

		GLuint Shader::buildShader(const char* path, GLenum shaderType) {
			GLuint shaderID = glCreateShader(shaderType);
			std::string content = FileUtils::read_file(path);
			const char* source = content.c_str();

			glShaderSource(shaderID, 1, &source, NULL);
			glCompileShader(shaderID);

			GLint result;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(shaderID, length, &length, &error[0]);
				std::cout << "Shader file (" << path << ") has errors!" << std::endl << &error[0] << std::endl;
				glDeleteShader(shaderID);
				return 0;
			}
			return shaderID;
		}
	};
}