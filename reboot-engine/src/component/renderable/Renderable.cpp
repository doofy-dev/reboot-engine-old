#include "Renderable.h"

#include "../../entity/gameObject.h"
#include "../physics/transform.h"

namespace reboot {
	namespace component {

		Renderable::Renderable(driver::IndexBuffer* ibo, driver::VertexArray* vao, driver::shader::Material* material):Component("Renderable"){
			renderMode = GL_TRIANGLES;
			m_Material = material;
			indexBuffer = ibo;
			vertexArray = vao;
			m_ModelMatrixLocation = m_Material->getUniformLocation("mvp.model");
			//*/
		}

		Renderable::~Renderable() {
			delete indexBuffer;
			delete m_Material;
			delete vertexArray;
		}

		void Renderable::bind() {
			m_Material->load();
			if(gameObject!=nullptr)
				m_Material->shader->loadUniformMat4f(m_ModelMatrixLocation, gameObject->transform->getTransformationMatrix());
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