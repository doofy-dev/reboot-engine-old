#include "fileUtils.h"

namespace reboot {
	namespace driver {
		std::string FileUtils::read_file(const char* filepath) {
			FILE* file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}

		IndexBuffer* FileUtils::load_obj(VertexArray* vao, const char* path) {
			using namespace maths;
			Assimp::Importer importer;
			std::vector<unsigned short> indices;
			std::vector<float> vertices;
			std::vector<float> uvs;
			std::vector<float> normals;

			// And have it read the given file with some example postprocessing
			// Usually - if speed is not the most important aspect for you - you'll 
			// propably to request more postprocessing than we do in this example.
			const aiScene* scene = importer.ReadFile(path,0);

			// If the import failed, report it
			if (!scene)
			{
				std::cout << "Failed to load model!" << std::endl;
				return nullptr;
			}
	//		for (unsigned int j = 0; j<scene->mNumMeshes; j++) {

				const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

														// Fill vertices positions
				vertices.reserve(mesh->mNumVertices);
				for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
					aiVector3D pos = mesh->mVertices[i];
					vertices.push_back(pos.x);
					vertices.push_back( pos.y);
					vertices.push_back( pos.z);
				}

				// Fill vertices texture coordinates
				uvs.reserve(mesh->mNumVertices);
				for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
					aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
					uvs.push_back(UVW.x);
					uvs.push_back(UVW.y);
				}
				
				// Fill vertices normals
				normals.reserve(mesh->mNumVertices);
				for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
					aiVector3D n = mesh->mNormals[i];
					normals.push_back(n.x);
					normals.push_back(n.y);
					normals.push_back(n.z);
				}


				// Fill face indices
				indices.reserve(3 * mesh->mNumFaces);
				for (unsigned int i = 0; i<mesh->mNumFaces; i++) {
					// Assume the model has only triangles.
					indices.push_back(mesh->mFaces[i].mIndices[0]);
					indices.push_back(mesh->mFaces[i].mIndices[1]);
					indices.push_back(mesh->mFaces[i].mIndices[2]);
				}
	//		}

			vao->addBuffer(new Buffer(&vertices[0],vertices.size(),  3), 0);
			vao->addBuffer(new Buffer(&uvs[0], uvs.size(), 2), 1);
			vao->addBuffer(new Buffer(&normals[0],normals.size(), 3), 2);
			return new IndexBuffer(&indices[0], indices.size());;
		}
	}
}