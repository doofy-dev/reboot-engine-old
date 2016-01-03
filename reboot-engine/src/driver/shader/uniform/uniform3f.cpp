#include "uniform3f.h"

namespace reboot {
	namespace driver {
		namespace shader {
			Uniform3f::Uniform3f(const char* name, GLuint shaderID) :UniformValue(name, shaderID) {

			}

			Uniform3f::~Uniform3f() {

			}

			void Uniform3f::setValue(maths::vec3& value) {
				m_Value = value;
			}

			void Uniform3f::load() {
				UniformValue::load(UniformValue::getLocation(), m_Value);
			}

			maths::vec3& Uniform3f::getValue() {
				return m_Value;
			}
		}
	}
}