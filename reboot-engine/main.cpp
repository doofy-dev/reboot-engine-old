#include "src/driver/window/window.h"
#include "src/driver/shader/shader.h"

#include "src/driver/buffer/buffer.h"
#include "src/driver/buffer/indexBuffer.h"
#include "src/driver/buffer/vertexArray.h"
#include "src/driver/buffer/frameBuffer.h"

#include "src/math/maths.h"

int main() {
	using namespace reboot;
	using namespace driver;
	using namespace maths;

	Window window("My window", 1366, 768);


	std::cout << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);

	GLfloat verticles[] = {
		0.0f,	0.0f,	0.0f,
		0.0f,	3.0f,	0.0f,
		8.0f,	3.0f,	0.0f,
		8.0f,	0.0f,	0.0f,
	};

	GLfloat textureCoords[] = {
		0,0,
		0,1,
		1,1,
		1,0
	};

	GLushort indices[] = {
		0,1,2,
		2,3,0
	};

	GLfloat colorsA[] = {
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1
	};
	GLfloat colorsB[] = {
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};
	
//  NULLING instance
//	VertexArray* vaoC = nullptr;

	VertexArray vaoA, vaoB;
	
	IndexBuffer ibo(indices, 6);
	FrameBuffer buffer(1366, 768);
	
	vaoA.addBuffer(new Buffer(verticles, 4 * 3, 3), 0);
	vaoA.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);
	vaoA.addBuffer(new Buffer(textureCoords, 2 * 4, 2), 2);
	vaoB.addBuffer(new Buffer(verticles, 4 * 3, 3), 0);
	vaoB.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);
	vaoB.addBuffer(new Buffer(textureCoords, 2 * 4, 2), 2);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();
	shader.loadUniformMat4f("pr_matrix", ortho);
	mat4 transformation = mat4::translation(vec3(4, 3, 0));
//	transformation *= mat4::rotation(0, vec3(0, 0, 1));
//	transformation *= mat4::scale(vec3(8, 8, 0));
	shader.loadUniformMat4f("ml_matrix", transformation);
	
	//shader.loadUniform4f("colour", vec4(0.0f, 1.0f, 1.0f, 1.0f));
	shader.loadUniform2f("light_pos", vec2(0, 0));


	while (!window.closed())
	{

		buffer.bind();
		window.clear();
		
		double x, y;
		window.getMousePosition(x, y);

		shader.loadUniform2f("light_pos", vec2((float)(x* 16.0f / (float)window.getWidht()), (float)(9.0f - y* 9.0f / (float)window.getHeight())));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
		vaoA.bind();
		ibo.bind();

		shader.loadUniformMat4f("ml_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		
		ibo.unbind();
		vaoA.unbind();

		vaoB.bind();
		ibo.bind();

		shader.loadUniformMat4f("ml_matrix", mat4::translation(vec3(0,0,0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

		ibo.unbind();
		vaoB.unbind();
	//	std::cout << fps << " FPS" << std::endl;
		window.update();


		buffer.unbind();

		window.clear();

		window.getMousePosition(x, y);

		shader.loadUniform2f("light_pos", vec2((float)(x* 16.0f / (float)window.getWidht()), (float)(9.0f - y* 9.0f / (float)window.getHeight())));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
		vaoA.bind();
		ibo.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, buffer.getTextureID());
		shader.loadUniformMat4f("ml_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

		ibo.unbind();
		vaoA.unbind();

		//	std::cout << fps << " FPS" << std::endl;
		window.update();

	}
	return 0;
}

