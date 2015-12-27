#pragma once

#include "uniformValue.h"

namespace reboot {
	namespace driver {
		namespace shader {
			using namespace maths;
			class Uniform1i : public UniformValue {
			private:
				int m_Value;
			public:

				Uniform1i(const char* name, GLuint shaderID);
				virtual ~Uniform1i();

				void load();
				void setValue(int value);
				int getValue();
			};
		}
	}
}
