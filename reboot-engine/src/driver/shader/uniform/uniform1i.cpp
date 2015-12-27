#include "uniform1i.h"

namespace reboot {
	namespace driver {
		namespace shader {
			Uniform1i::Uniform1i(const char* name, GLuint shaderID) :UniformValue(name, shaderID) {

			}

			Uniform1i::~Uniform1i() {

			}

			void Uniform1i::setValue(int value) {
				m_Value = value;
			}

			void Uniform1i::load() {
				UniformValue::load(UniformValue::getLocation(), m_Value);
			}

			int Uniform1i::getValue() {
				return m_Value;
			}
		}
	}
}