#pragma once

#include "vec3.h"
#include "convert.h"

namespace reboot {
	namespace maths {


		struct mat4
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;

			mat4();
			mat4(float diagonal);

			static mat4 identity();

			void getArray(float(&data)[16]) const;

			mat4& multiply(const mat4& right);
			mat4& set(float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33);
			friend mat4 operator*(mat4 left, const mat4& right);
			mat4& operator*=(const mat4& other);

			static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);

			static mat4 translation(const vec3& translation);
			static mat4 rotation(float angle, const vec3& axis);
			static mat4 scale(const vec3& scale);

			friend mat4 operator*(mat4 left, const mat4& right);
			friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
		};
	
	}
}