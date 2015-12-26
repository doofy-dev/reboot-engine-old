#include "mat4.h"

namespace reboot {
	namespace maths {
	
		mat4::mat4() {
			m00 = m01 = m02 = m03 =
			m10 = m11 = m12 = m13 =
			m20 = m21 = m22 = m23 =
			m30 = m31 = m32 = m33 = 0;
		}

		mat4::mat4(float diagonal) {

			m01 = m02 = m03 =
			m10 = m12 = m13 =
			m20 = m21 = m23 =
			m30 = m31 = m32 = 0;
			
			m00 = diagonal;
			m11 = diagonal;
			m22 = diagonal;
			m33 = diagonal;
		}

		mat4 mat4::identity() {
			return mat4(1.0f);
		}

		mat4 operator*(mat4 left, const mat4& right) {
			return left.multiply(right);
		}

		mat4& mat4::operator*=(const mat4& other) {
			return multiply(other);
		}

		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			mat4 result(1.0f);

			result.m00 = 2.0f / (right - left);
			result.m11 = 2.0f / (top - bottom);
			result.m22 = 2.0f / (near - far);

			result.m03 = (left + right) / (left - right);
			result.m13 = (bottom + top) / (bottom - top);
			result.m23 = (far + near) / (far - near);

			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) {
			mat4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f*fov));
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.m00 = a;
			result.m11 = q;
			result.m22 = b;
			result.m32 = -1.0f;
			result.m23 = c;
			
			return result;
		}

		mat4 mat4::translation(const vec3& translation) {
			mat4 result(1.0f);

			result.m03 = translation.x;
			result.m13 = translation.y;
			result.m23 = translation.z;
			return result;
		}

		mat4 mat4::scale(const vec3& scale) {
			mat4 result(1.0f);
			result.m00 = scale.x;
			result.m11 = scale.y;
			result.m22 = scale.z;
			return result;
		}

		mat4 mat4::rotation(float angle, const vec3& axis) {
			mat4 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;
			
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.m00 = x * omc + c;
			result.m10 = y * x * omc + z * s;
			result.m20 = x * z * omc - y * s;

			result.m01 = x * y * omc - z * s;
			result.m11 = y * omc + c;
			result.m21 = y * z * omc + x * s;

			result.m02 = x * z * omc + y * s;
			result.m12 = y * z * omc - x * s;
			result.m22 = z * omc + c;

			return result;
		}

		mat4& mat4::multiply(const mat4& right) {
			set(m00 * right.m00 + m10 * right.m01 + m20 * right.m02 + m30 * right.m03,
				m01 * right.m00 + m11 * right.m01 + m21 * right.m02 + m31 * right.m03,
				m02 * right.m00 + m12 * right.m01 + m22 * right.m02 + m32 * right.m03,
				m03 * right.m00 + m13 * right.m01 + m23 * right.m02 + m33 * right.m03,
				m00 * right.m10 + m10 * right.m11 + m20 * right.m12 + m30 * right.m13,
				m01 * right.m10 + m11 * right.m11 + m21 * right.m12 + m31 * right.m13,
				m02 * right.m10 + m12 * right.m11 + m22 * right.m12 + m32 * right.m13,
				m03 * right.m10 + m13 * right.m11 + m23 * right.m12 + m33 * right.m13,
				m00 * right.m20 + m10 * right.m21 + m20 * right.m22 + m30 * right.m23,
				m01 * right.m20 + m11 * right.m21 + m21 * right.m22 + m31 * right.m23,
				m02 * right.m20 + m12 * right.m21 + m22 * right.m22 + m32 * right.m23,
				m03 * right.m20 + m13 * right.m21 + m23 * right.m22 + m33 * right.m23,
				m00 * right.m30 + m10 * right.m31 + m20 * right.m32 + m30 * right.m33,
				m01 * right.m30 + m11 * right.m31 + m21 * right.m32 + m31 * right.m33,
				m02 * right.m30 + m12 * right.m31 + m22 * right.m32 + m32 * right.m33,
				m03 * right.m30 + m13 * right.m31 + m23 * right.m32 + m33 * right.m33);
			return *this;
		}


		mat4& mat4::set(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33) {
			this->m00 = m00;
			this->m01 = m01;
			this->m02 = m02;
			this->m03 = m03;
			this->m10 = m10;
			this->m11 = m11;
			this->m12 = m12;
			this->m13 = m13;
			this->m20 = m20;
			this->m21 = m21;
			this->m22 = m22;
			this->m23 = m23;
			this->m30 = m30;
			this->m31 = m31;
			this->m32 = m32;
			this->m33 = m33;
			return *this;
		}

		void mat4::getArray(float(&data)[16]) const {
			data[0] = m00;
			data[1] = m10;
			data[2] = m20;
			data[3] = m30;

			data[4] = m01;
			data[5] = m11;
			data[6] = m21;
			data[7] = m31;

			data[8] = m02;
			data[9] = m12;
			data[10] = m22;
			data[11] = m32;

			data[12] = m03;
			data[13] = m13;
			data[14] = m23;
			data[15] = m33;
		}

		std::ostream& operator<<(std::ostream& stream, const mat4& matrix) {
			stream	<< "mat4 |" << matrix.m00 << ", " << matrix.m01 << ", " << matrix.m02 << ", " << matrix.m03 << "|" << std::endl
					<< "     |" << matrix.m10 << ", " << matrix.m11 << ", " << matrix.m12 << ", " << matrix.m13 << "|" << std::endl
					<< "     |" << matrix.m20 << ", " << matrix.m21 << ", " << matrix.m22 << ", " << matrix.m23 << "|" << std::endl
					<< "     |" << matrix.m30 << ", " << matrix.m31 << ", " << matrix.m32 << ", " << matrix.m33 << "|" << std::endl
				;
			return stream;
		}
	}
}