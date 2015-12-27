#include "Renderable.h"

namespace reboot {
	namespace component {

		Renderable::Renderable(driver::IndexBuffer* ibo, driver::VertexArray* vao, driver::shader::Material* material):Component("Renderable") {
			renderMode = GL_TRIANGLES;
			m_Material = material;
			indexBuffer = ibo;
			vertexArray = vao;
		}

		Renderable::~Renderable() {
			delete indexBuffer;
			delete vertexArray;
		}

		void Renderable::prepare() {

		}

	}
}