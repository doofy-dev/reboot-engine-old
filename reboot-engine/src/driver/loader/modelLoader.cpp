#include "modelLoader.h"
#include "../../driver/buffer/vertexArray.h"
#include "../../component/renderable/Renderable.h"
#include "../../driver/buffer/buffer.h"
#include "../shader/uniform/uniform4f.h"
#include "../shader/uniform/uniform1i.h"
#include "../../driver/buffer/indexBuffer.h"
#include "../../driver/buffer/vertexArray.h"
#include "../../driver/shader/texture/texture.h"

namespace reboot {
	namespace driver {

	
		entity::GameObject* ModelLoader::loadModel(const char* path, const char* file, renderer::Scene* sceneInstance) {
			unsigned int numFaces = 0;
			shader::Material* material = new shader::Material("shaders/basic.vert", "shaders/basic.frag");
			Assimp::Importer importer;
			std::string f = path;
			f.append(file);
			const aiScene* scene = importer.ReadFile(f, aiProcess_CalcTangentSpace | aiProcess_Triangulate  | aiProcess_SortByPType);
			entity::GameObject* holder = new entity::GameObject(file);
			std::vector<shader::Material*> materials ;

			if (scene->HasMaterials())
			{
				for (unsigned int i = 0; i < scene->mNumMaterials; i++)
				{
					const aiMaterial* material = scene->mMaterials[i];

					shader::Uniform1i* use = new shader::Uniform1i("use_color", 0);
					int USECOLOR = 0;
					aiString texturePath;
					shader::Material* mat = new shader::Material("shaders/basic.vert", "shaders/basic.frag");					unsigned int numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);   // always 0

					if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0 && material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
					{
						std::cout << texturePath.C_Str() << std::endl;
						std::string s = path;
						s.append(texturePath.C_Str());
						mat->addTexture(GL_TEXTURE0,new shader::Texture(s.c_str()));
						// never happens..
						// scene->mNumTextures is always 0 aswell.
					}
					else {
						aiColor4D diffuse;
						if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse)) {
							shader::Uniform4f* col = new shader::Uniform4f("face_color", 0);
							USECOLOR = 1;
							col->setValue(vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
							mat->addUniform(col);
						}
					}
					use->setValue(USECOLOR);
					mat->addUniform(use);
					materials.push_back(mat);
				}
			}

			for (unsigned int n = 0; n < scene->mNumMeshes; ++n) {
				const aiMesh* mesh = scene->mMeshes[n];
				Buffer* texture = nullptr;
				Buffer* normals = nullptr;
				Buffer* vertices = nullptr;
				IndexBuffer* ibo = nullptr;
				VertexArray* vao = new VertexArray();

				unsigned int* faceArray;

				int textureID = 0;

#define MALLOC

#ifndef MALLOC
				faceArray = new unsigned int[mesh->mNumFaces * 3];
				for (unsigned int t = 0; t < mesh->mNumFaces; t++) {
					//const aiFace* face = &;
					faceArray[t * 3] = mesh->mFaces[t].mIndices[0];
					faceArray[t * 3 + 1] = mesh->mFaces[t].mIndices[1];
					faceArray[t * 3 + 2] = mesh->mFaces[t].mIndices[2];
				}
#else
				faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
				unsigned int faceIndex=0;
				for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
					const aiFace* face = &mesh->mFaces[t];
					
					memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
					faceIndex += 3;
				}
#endif
				numFaces = scene->mMeshes[n]->mNumFaces*3;
				vao->bind();
				ibo = new IndexBuffer(faceArray, numFaces);
				/*
				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);

				glGenBuffers(1, &buffer);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);
				*/
				// buffer for vertex positions
				if (mesh->HasPositions()) {
					vertices = new Buffer(mesh->mVertices, 3 * mesh->mNumVertices, 3);
		/*			glGenBuffers(1, &buffer);
					glBindBuffer(GL_ARRAY_BUFFER, buffer);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
					*/
				}

				// buffer for vertex normals
				if (mesh->HasNormals()) {
					normals = new Buffer(mesh->mNormals, 3 * mesh->mNumVertices, 3);
		/*			glGenBuffers(1, &buffer);
					glBindBuffer(GL_ARRAY_BUFFER, buffer);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);
					*/
				}
				// buffer for vertex texture coordinates
				if (mesh->HasTextureCoords(0)) {
					float *texCoords = (float *)malloc(sizeof(float) * 2 * mesh->mNumVertices);
					for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {

						texCoords[k * 2] = mesh->mTextureCoords[0][k].x;
						texCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
					}
					texture = new Buffer(texCoords, 2 * mesh->mNumVertices, 2);
/*					glGenBuffers(1, &buffer);
					glBindBuffer(GL_ARRAY_BUFFER, buffer);
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);
	*/			}
				textureID = mesh->mMaterialIndex;
				vao->unbind();
				if(vertices!=nullptr)
					vao->addBuffer(vertices, 0);
				if(texture!=nullptr)
					vao->addBuffer(texture, 1);
				if(normals!=nullptr)
					vao->addBuffer(normals, 2);

				/*GLenum face_mode = GL_TRIANGLES;
				switch (mesh->mFaces[0].mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
				}
				*/
				//textureID = (textureID != 0 ? textureID - 1 : 0);
				if (materials.size() == 0)
					materials.push_back(material);
				else if(materials.size()<=textureID) {
					textureID = 0;
				}
				component::Renderable* renderable = new component::Renderable(ibo, vao, materials[textureID]);
				renderable->setRendeMode(GL_TRIANGLES);
				entity::GameObject* go = new entity::GameObject("Mesh");
				go->addCompontent(renderable);
				go->instantinate(sceneInstance);
			}

#ifdef OLD

			if (!scene)
			{
				std::cout << "Failed to load model!" << std::endl;
				return nullptr;
			}

			for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
				GLuint* indices = nullptr;
				GLfloat *verticles = nullptr;
				GLfloat *uvs = nullptr;
				GLfloat *normals = nullptr; 
				std::vector<GLuint> indi;
		
				const aiMesh* mesh = scene->mMeshes[m];

				if (mesh->HasPositions()) {
					verticles = new GLfloat[mesh->mNumVertices * 3];
					for (int i = 0; i < mesh->mNumVertices; ++i) {
						verticles[i*3] = mesh->mVertices[i].x;
						verticles[i*3+1] = mesh->mVertices[i].y;
						verticles[i*3+2]=mesh->mVertices[i].z;
					}
				}
				if (mesh->HasNormals()) {
					normals = new GLfloat[mesh->mNumVertices * 3];
					for (int i = 0; i < mesh->mNumVertices; ++i) {
						normals[i * 3] = mesh->mNormals[i].x;
						normals[i * 3 + 2] = mesh->mNormals[i].y;
						normals[i * 3 + 2]= mesh->mNormals[i].z;
					}
				}
				if (mesh->HasTextureCoords(0)) {
					uvs = new GLfloat[mesh->mNumVertices * 2];
					for (int i = 0; i < mesh->mNumVertices; ++i) {
						uvs[i * 2] = mesh->mTextureCoords[0][i].x;
						uvs[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
					}
				} 
				GLenum face_mode = GL_TRIANGLES;
				if (mesh->HasFaces()) {
					switch (mesh->mFaces[0].mNumIndices) {
					case 1: face_mode = GL_POINTS; break;
					case 2: face_mode = GL_LINES; break;
					case 3: face_mode = GL_TRIANGLES; break;
					default: face_mode = GL_POLYGON; break;
					}
					//indices = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
					for (int i = 0; i < mesh->mNumFaces; ++i) {
						//if (mesh->mFaces[i].mNumIndices == 3) {
						for (int j = 0; j < mesh->mFaces[i].mNumIndices;++j)
							indi.push_back(mesh->mFaces[i].mIndices[j]);
						/*	indices[i * 3] = mesh->mFaces[i].mIndices[0];
							indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
							indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];*/
					//	}
					}
				}
				shader::Material* material = new shader::Material("shaders/basic.vert", "shaders/basic.frag");
				VertexArray* vao = new VertexArray();
				if(verticles!=nullptr)
					vao->addBuffer(new Buffer(verticles, mesh->mNumVertices*3, 3), 0);
				if (uvs != nullptr)
					vao->addBuffer(new Buffer(uvs, mesh->mNumVertices*2, 2), 1);
				if (normals != nullptr)
					vao->addBuffer(new Buffer(normals, mesh->mNumVertices*3, 3), 2);
				IndexBuffer* ibo = new IndexBuffer(&indi[0], indi.size());
				component::Renderable* renderable = new component::Renderable(ibo, vao, material);
				renderable->setRendeMode(face_mode);
				entity::GameObject* go = new entity::GameObject("Mesh");
				go->addCompontent(renderable);
				go->instantinate(sceneInstance);
				
		//	return go;
				//holder->addChild(go);
			}
			//*/
		/*	std::vector<shader::Material*> materials;
			for (unsigned int j = 0; j < scene->mNumMaterials; j++) {
				int texIndex = 0; 
				aiString path;  // filename

				shader::Material material("shaders/basic.vert", "shaders/basic.frag");
				aiReturn texFound = scene->mMaterials[j]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
				while (texFound == AI_SUCCESS) {
					// more textures?
					texIndex++;
					texFound = scene->mMaterials[j]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
				}
			}
			*/

		/*	std::vector<unsigned short> indices;
			std::vector<float> vertices;
			std::vector<float> uvs;
			std::vector<float> normals;
			for (unsigned int j = 0; j < scene->mNumMeshes; j++) {
	//		int j = 0;

				const aiMesh* mesh = scene->mMeshes[j];
		//		vertices.reserve(mesh->mNumVertices);
				for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
					aiVector3D pos = mesh->mVertices[i];
					vertices.push_back(pos.x);
					vertices.push_back(pos.y);
					vertices.push_back(pos.z);
				}

				// Fill vertices texture coordinates
			//	uvs.reserve(mesh->mNumVertices);
				for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
					aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
					uvs.push_back(UVW.x);
					uvs.push_back(UVW.y);
				}

				// Fill vertices normals
		//		normals.reserve(mesh->mNumVertices);
				for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
					aiVector3D n = mesh->mNormals[i];
					normals.push_back(n.x);
					normals.push_back(n.y);
					normals.push_back(n.z);
				}


				// Fill face indices
	//			indices.reserve(3 * mesh->mNumFaces);
				for (unsigned int i = 0; i<mesh->mNumFaces; i++) {
					// Assume the model has only triangles.
					indices.push_back(mesh->mFaces[i].mIndices[0]);
					indices.push_back(mesh->mFaces[i].mIndices[1]);
					indices.push_back(mesh->mFaces[i].mIndices[2]);
				}

		
			//	return go;
			
			}
			shader::Material* material = new shader::Material("shaders/basic.vert", "shaders/basic.frag");
			VertexArray* vao = new VertexArray();
			vao->addBuffer(new Buffer(&vertices[0], vertices.size(), 3), 0);
			vao->addBuffer(new Buffer(&uvs[0], uvs.size(), 2), 1);
			vao->addBuffer(new Buffer(&normals[0], normals.size(), 3), 2);
			IndexBuffer* ibo = new IndexBuffer(&indices[0], indices.size());
			component::Renderable* renderable = new component::Renderable(ibo, vao, material);
			entity::GameObject* go = new entity::GameObject("Mesh");
			go->addCompontent(renderable);
			holder->addChild(go);
			//*/

#endif // DEBUG

			return holder;
		}
	}
}