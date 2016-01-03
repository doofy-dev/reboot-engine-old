#include "uniform4f.h"

namespace reboot {
	namespace driver {
		namespace shader {
			Uniform4f::Uniform4f(const char* name, GLuint shaderID) :UniformValue(name, shaderID) {

			}

			Uniform4f::~Uniform4f() {

			}

			void Uniform4f::setValue(maths::vec4& value) {
				m_Value = value;
			}

			void Uniform4f::load() {
				UniformValue::load(UniformValue::getLocation(), m_Value);
			}

			maths::vec4& Uniform4f::getValue() {
				return m_Value;
			}
		}
	}
}