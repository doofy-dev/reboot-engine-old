#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "../../math/maths.h"
#include "../../entity/gameObject.h"
#include "../../driver/shader/shader.h"



namespace reboot {
	namespace driver {
		class ModelLoader {
		public:
//			static entity::GameObject loadFolder(const char *path);
			static entity::GameObject* loadModel(const char* path, const char* file, renderer::Scene* scene);
		};
	}
}