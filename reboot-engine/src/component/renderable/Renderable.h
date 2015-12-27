#pragma once

#include <GL/glew.h>
#include "../component.h"
#include "../../driver/buffer/buffer.h"
#include "../../driver/buffer/indexBuffer.h"
#include "../../driver/buffer/vertexArray.h"
#include "../../driver/shader/shader.h"
#include "../../driver/shader/material/material.h"

namespace reboot {
	namespace component {
		class Renderable : public Component {
		private:
			driver::IndexBuffer* indexBuffer;
			driver::VertexArray* vertexArray;
			GLuint renderMode;
			driver::shader::Material* m_Material;
		public:
			Renderable(driver::IndexBuffer* ibo, driver::VertexArray* vao, driver::shader::Material* material);
			~Renderable();
			
			inline void Renderable::addBuffer(driver::Buffer* buffer, unsigned short location){ vertexArray->addBuffer(buffer, location); }
			inline void Renderable::setRendeMode(unsigned short renderMode) { this->renderMode = renderMode; }
			inline driver::IndexBuffer* getIBO() { return indexBuffer; }
			inline driver::VertexArray* getVAO() { return vertexArray; }
			inline driver::shader::Material* getMaterial() { return m_Material; }
			void prepare();
		};
	}
}