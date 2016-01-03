#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "../../math/maths.h"
#include "../buffer/vertexArray.h"
#include "../buffer/indexBuffer.h"
#include "../buffer/buffer.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace reboot {
	namespace driver {
		class FileUtils {
		public:
			static std::string read_file(const char* filepath);
			static IndexBuffer* load_obj(VertexArray* vao, const char* filepath);
		};
	}
}

