#pragma once

#include "uniformValue.h"

namespace reboot {
	namespace driver {
		namespace shader {
			using namespace maths;
			class Uniform3f : public UniformValue {
			private:
				maths::vec3* m_Value;
			public:

				Uniform3f(const char* name, GLuint shaderID);
				virtual ~Uniform3f();

				void load();
				void setValue(maths::vec3* value);
				maths::vec3* getValue();
			};
		}
	}
}
