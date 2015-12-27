#pragma once

#include "uniformValue.h"

namespace reboot {
	namespace driver {
		namespace shader {
			using namespace maths;
			class Uniform1f : public UniformValue {
			private:
				float m_Value;
			public:

				Uniform1f(const char* name, GLuint shaderID);
				virtual ~Uniform1f();

				void load();
				void setValue(float value);
				float getValue();
			};
		}
	}
}
