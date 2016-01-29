#include "texture.h"

namespace reboot {
	namespace driver {
		namespace shader {

			Texture::Texture(const char* path) {
				textureID = SOIL_load_OGL_texture
					(
						path,
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);
				if (0 > textureID)
				{
					std::cout << "SOIL loading error: "<<SOIL_last_result()<<std::endl;
				}

			}

			Texture::Texture(GLuint textureID):textureID(textureID){}

			Texture::~Texture() {
				if (0 > textureID)
					glDeleteTextures(1, &textureID);
			}

			void Texture::bind(GLuint location) {
				if (0 <= textureID) {
					glActiveTexture(location);
					glBindTexture(GL_TEXTURE_2D, textureID);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
			}

			void Texture::unbind() {
				glBindTexture(GL_TEXTURE_2D, 0);
			}

		}
	}
}