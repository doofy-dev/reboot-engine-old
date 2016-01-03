#include "uniformMat4.h"

namespace reboot {
	namespace driver {
		namespace shader {
			UniformMat4::UniformMat4(const char* name, GLuint shaderID) :UniformValue(name, shaderID) {

			}

			UniformMat4::~UniformMat4() {

			}

			void UniformMat4::setValue(maths::mat4& value) {
				m_Value = value;
			}

			void UniformMat4::load() {
		//		std::cout << "Loading matrix into "<< m_Location <<std::endl << m_Value << std::endl;
				UniformValue::load(UniformValue::getLocation(), m_Value);
			}

			maths::mat4& UniformMat4::getValue() {
				return m_Value;
			}
		}
	}
}