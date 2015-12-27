#pragma once

#include <GL/glew.h>
#include "../../../math/maths.h"

namespace reboot {
	namespace driver {
		namespace shader {
			using namespace maths;
			class UniformValue {
			private:
				const char* m_Name;
				GLint m_Location;

			public:
				UniformValue(const char* name, GLuint shaderID);
				void connectToShader(GLuint shaderID);
				virtual ~UniformValue();
				void load(GLint location, float value);
				void load(GLint location, int value);

				void load(GLint location, const vec2& value);
				void load(GLint location, const vec3& value);
				void load(GLint location, const vec4& value);

				void load(GLint location, const mat4& uniform);

				GLint getLocation() { return m_Location; }
				const char* getName() { return m_Name; }
			};
		}
	}
}