#pragma once

#include "uniformValue.h"

namespace reboot {
	namespace driver {
		namespace shader {
			using namespace maths;
			class Uniform4f : public UniformValue {
			private:
				maths::vec4 m_Value;
			public:

				Uniform4f(const char* name, GLuint shaderID);
				virtual ~Uniform4f();

				void load();
				void setValue(maths::vec4& value);
				maths::vec4& getValue();
			};
		}
	}
}
