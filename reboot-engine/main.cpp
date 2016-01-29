#include "src/driver/window/window.h"
#include "src/driver/shader/shader.h"

#include "src/driver/buffer/buffer.h"
#include "src/driver/buffer/indexBuffer.h"
#include "src/driver/buffer/vertexArray.h"
#include "src/driver/buffer/frameBuffer.h"

#include "src/math/maths.h"
#include "src/driver/shader/uniform/uniform1i.h"

#include "src/renderer/scene/scene.h"
#include "src/renderer/engine/renderer.h"
#include "src/entity/gameObject.h"
#include "src/entity/camera.h"
#include "src/component/renderable/Renderable.h"
#include "src/component/physics/transform.h"
#include "src/component/control/freeMove.h"
#include "src/driver/shader/uniform/uniformMat4.h"
#include "src/driver/shader/uniform/uniform2f.h"
#include "src/driver/shader/uniform/uniform4f.h"
#include "src/driver/shader/uniform/uniform3f.h"
#include "src\driver\audio\audioSource.h"
#include "src/driver/loader/modelLoader.h"

#include <stdlib.h>
#include <time.h>
#include <SOIL.h>

int main() {
	using namespace reboot;
	using namespace driver;
	using namespace shader;
	using namespace maths;
	using namespace renderer;
	using namespace entity;
	using namespace component;

	Window* window = new Window("My window", 1366, 768);
	renderer::Scene* scene = new Scene("Scene 1");

	//srand(time(NULL));

	Renderer rend(scene, window);


	std::cout << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);

	GLfloat verticles[] = {
		//BACK
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		//FRONT
		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		//RIGHT
		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		//LEFT
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		//TOP
		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		//BOTTOM
		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f
	};

	GLfloat textureCoords[] = {
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0
	};

	GLushort indices[] = {
		//BACK
		0,3,1,
		1,3,2,

		//FRONT
		4,5,7,
		7,5,6,

		//RIGHT
		8,11,9,
		9,11,10,

		//LEFT
		12,13,15,
		15,13,14,

		//TOP
		16,19,17,
		17,19,18,

		//BOTTOM
		20,21,23,
		23,21,22
	};

	GLfloat normals[] = {
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f
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

	VertexArray *vaoA, vaoB;
	
//	FrameBuffer buffer(1366, 768);
	vaoA = new VertexArray();
	vaoA->addBuffer(new Buffer(verticles, 6 * 4 * 3, 3), 0);
	vaoA->addBuffer(new Buffer(textureCoords, 6 * 4 * 2, 2), 1);
	vaoA->addBuffer(new Buffer(normals, 6 * 4 * 3, 3), 2);

	VertexArray* vao = new VertexArray();
	IndexBuffer* ibo = FileUtils::load_obj(vao, "res/frigate.obj");
	

	//vaoA->addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

	vaoB.addBuffer(new Buffer(verticles, 4 * 3, 3), 0);
	vaoB.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	mat4 perspective = mat4::perspective(90, 16.0f / 9.0f, 0.01f, 1000);

	mat4 transformation = mat4::translation(vec3(0, 0, -30))* mat4::scale(vec3(0.3f,0.3f,0.3f));


	
	//Texture brick("res/frigate.png");
	Texture brick("res/building/125_0013.jpg");

	GameObject* go = new GameObject("GO1");
	Material* material = new Material("shaders/basic.vert", "shaders/basic.frag");

	/*UniformMat4 pr_matrix("mvp.projection",0);
	pr_matrix.setValue(perspective);
	//go->transform->setPosition(vec3(0, 0, -5));
	/*
	UniformMat4 ml_matrix("mvp.model", 0);
	ml_matrix.setValue(transformation);
	//*/

	/*Uniform4f colour("colour", 0);
	colour.setValue(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	*/
	Uniform2f light_pos("light_pos", 0);
	light_pos.setValue(vec2(0.0f, 0.0f));

	//material->addUniform(&pr_matrix);
	//material->addUniform(&colour);
	go->transform->setPosition(vec3(0, 0, -30));
	go->transform->setScale(vec3(0.3f, 0.3f, 0.3f));
	//material->addUniform(&ml_matrix);
	/*
	material->addUniform(new UniformMat4("mvp.model", 0));
	material->addUniform(new UniformMat4("mvp.view", 0));
	material->addUniform(new UniformMat4("mvp.projection", 0));
	//*/
	material->addUniform(&light_pos);
	material->addTexture(GL_TEXTURE0, &brick);

	Renderable renderable(ibo, vao, material);
	go->addCompontent(&renderable);
	//scene->assingGameObject(go);
	
	//GameObject* loaded = ModelLoader::loadModel("res/paris/","Paris2010_0.obj",scene);
//	GameObject* loaded = ModelLoader::loadModel("res/iron-man/","Iron_Man_mark_42.obj",scene);
	//GameObject* loaded = ModelLoader::loadModel("res/","frigate.obj",scene);
	//GameObject* loaded = ModelLoader::loadModel("res/sci-fy_city/","Center City Sci-Fi.obj",scene);
	//GameObject* loaded = ModelLoader::loadModel("res/volkswagen/","Volkswagen Polo 1995 [obj].obj", scene);
	//GameObject* loaded = ModelLoader::loadModel("res/building/", "build.3ds", scene);
	//GameObject* loaded = ModelLoader::loadModel("res/atlantis/", "atlantis.obj", scene);
	GameObject* loaded = ModelLoader::loadModel("res/sirius/","sirus city.obj" , scene);
	//scene->assingGameObject(loaded);
	loaded->instantinate(scene);
#define NEWSYSTEM 1

#ifndef  NEWSYSTEM
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();
	shader.loadUniformMat4f("pr_matrix", ortho);
	//	transformation *= mat4::rotation(0, vec3(0, 0, 1));
	//	transformation *= mat4::scale(vec3(8, 8, 0));
	shader.loadUniformMat4f("ml_matrix", transformation);

	shader.loadUniform4f("colour", vec4(0.0f, 1.0f, 1.0f, 1.0f));
	shader.loadUniform2f("light_pos", vec2(0, 0));
	//*/
#endif // ! NEWSYSTEM


//	new AudioSource("res/wind.wav");
	PerspectiveCamera cam (1366,768);
	Camera camera(&cam,window);
	camera.addCompontent(new control::FreeMove(window));
	scene->assingGameObject(&camera);
//		ml_matrix.setValue(mat4::rotation(45, vec3(0, 1, 0)) * ml_matrix.getValue());
	while (!window->closed())
	{
		if (window->isKeyPressed(GLFW_KEY_ESCAPE))
			break;
#ifdef NEWSYSTEM
		rend.render(camera);
		rend.flush();
		window->setMouseGrabbed(window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT));
		/*double dx, dy;
		if (window->isGrabbed()) {
			window->getMouseMove(dx, dy);
			camera.transform->addRotation(maths::vec3(-dy / 5.0f, -dx / 5.0f, 0));
		}*/
	//	mat4 m = mat4::translation(vec3(1,2,0)) * (rand()%6-3);
	//	go->transform->addRotation(vec3(0, 0.1f, 0));
	//	ml_matrix.setValue(mat4::rotation(0.1f, vec3(0, 1, 0)) * ml_matrix.getValue());
		//ml_matrix.setValue(m);
#else
		window->clear();
		
		double x, y;
		window->getMousePosition(x, y);

		shader.loadUniform2f("light_pos", vec2((float)(x* 16.0f / (float)window->getWidht()), (float)(9.0f - y* 9.0f / (float)window->getHeight())));

		vaoA->bind();
		ibo->bind();

		shader.loadUniform4f("colour", vec4(0.0f, 1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_SHORT, 0);
		
		ibo->unbind();
		vaoA->unbind();

	//	std::cout << fps << " FPS" << std::endl;
		window->update();//*/

#endif

	}

//	getchar();
	return 0;
}

