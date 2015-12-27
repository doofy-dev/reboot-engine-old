#include "uniform1f.h"

namespace reboot {
	namespace driver {
		namespace shader {
			Uniform1f::Uniform1f(const char* name, GLuint shaderID) :UniformValue(name, shaderID) {

			}

			Uniform1f::~Uniform1f() {

			}

			void Uniform1f::setValue(float value) {
				m_Value = value;
			}

			void Uniform1f::load() {
				UniformValue::load(UniformValue::getLocation(), m_Value);
			}

			float Uniform1f::getValue() {
				return m_Value;
			}
		}
	}
}