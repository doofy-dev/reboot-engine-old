#pragma once

#include "uniformValue.h"

namespace reboot {
	namespace driver {
		namespace shader {
			using namespace maths;
			class Uniform2f : public UniformValue {
			private:
				maths::vec2* m_Value;
			public:

				Uniform2f(const char* name, GLuint shaderID);
				virtual ~Uniform2f();

				void load();
				void setValue(maths::vec2* value);
				maths::vec2* getValue();
			};
		}
	}
}
