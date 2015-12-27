#pragma once

#include "uniformValue.h"

namespace reboot {
	namespace driver {
		namespace shader {
			using namespace maths;
			class UniformMat4 : public UniformValue {
			private:
				maths::mat4* m_Value;
			public:

				UniformMat4(const char* name, GLuint shaderID);
				virtual ~UniformMat4();

				void load();
				void setValue(maths::mat4* value);
				maths::mat4* getValue();
			};
		}
	}
}
