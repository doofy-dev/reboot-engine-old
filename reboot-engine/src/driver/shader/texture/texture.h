#pragma once

#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

namespace reboot {
	namespace driver {
		namespace shader {

			class Texture {
			private:
				GLuint textureID;
			public:
				Texture(const char* path);
				Texture(GLuint textureID);
				~Texture();

				void bind(GLuint location);
				void unbind();

				inline GLuint Texture::getTextureID() { return textureID; }
			};

		}
	}
}