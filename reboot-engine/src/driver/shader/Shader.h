#pragma once

#include "../../math/maths.h"
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "../io/fileUtils.h"

namespace reboot {
	namespace driver {
		using namespace maths;

		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char *m_VertPath;
			const char *m_FragPath;
		public:
			Shader(const char *vertPath, const char *fragPath);
			~Shader();

			void enable() const;
			void disable() const;

			GLint getUniformLocation(const GLchar *name);

			void loadUniform1f(const GLchar *name, float value);
			void loadUniform1i(const GLchar *name, int value);

			void loadUniform2f(const GLchar *name, const vec2& value);
			void loadUniform3f(const GLchar *name, const vec3& value);
			void loadUniform4f(const GLchar *name, const vec4& value);

			void loadUniformMat4f(const GLchar *name, const mat4& uniform);

		private:
			GLuint load();
			GLuint buildShader(const char* path, GLenum shaderType);

		};


	}
}