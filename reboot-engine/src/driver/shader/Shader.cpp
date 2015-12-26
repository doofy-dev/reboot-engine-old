#include "shader.h"

namespace reboot {
	namespace driver {
		Shader::Shader(const char *vertPath, const char *fragPath) {
			m_VertPath = vertPath;
			m_FragPath = fragPath;

			m_ShaderID = load();
			if (m_ShaderID == 0)
				glDeleteProgram(m_ShaderID);
		}

		Shader::~Shader() {
			glDeleteProgram(m_ShaderID);
		}

		void Shader::enable() const {
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
			if (fragment == 0 || vertex == 0)
				return 0;

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