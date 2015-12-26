#pragma once

#include <string>

namespace reboot {
	namespace driver {
		class FileUtils {
		public:
			static std::string read_file(const char* filepath);
		};
	}
}

