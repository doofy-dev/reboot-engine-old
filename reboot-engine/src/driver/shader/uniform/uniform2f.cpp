#include "uniform2f.h"

namespace reboot {
	namespace driver {
		namespace shader {
			Uniform2f::Uniform2f(const char* name, GLuint shaderID) :UniformValue(name, shaderID){

			}

			Uniform2f::~Uniform2f() {

			}
			void Uniform2f::setValue(maths::vec2* value) {
				m_Value = value;
			}

			void Uniform2f::load() {
				UniformValue::load(UniformValue::getLocation(), *m_Value);
			}

			maths::vec2* Uniform2f::getValue() {
				return m_Value;
			}
		}
	}
}