#include "Renderable.h"

namespace reboot {
	namespace component {

		Renderable::Renderable(driver::IndexBuffer* ibo, driver::VertexArray* vao, driver::shader::Material* material):Component("Renderable"){
			renderMode = GL_TRIANGLES;
			m_Material = material;
			indexBuffer = ibo;
			vertexArray = vao;
			//*/
		}

		Renderable::~Renderable() {
			delete indexBuffer;
			delete m_Material;
			delete vertexArray;
		}

		void Renderable::bind() {
			m_Material->load();
			vertexArray->bind();
			indexBuffer->bind();
		}

		void Renderable::unbind() {
			m_Material->unload();
			indexBuffer->unbind();
			vertexArray->unbind();
		}
	}
}