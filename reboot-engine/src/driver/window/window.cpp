#include "window.h"


namespace reboot {
	namespace driver {
		bool Window::m_Keys[MAX_KEYS];
		bool Window::m_MouseButtons[MAX_BUTTONS];
		double Window::mx;
		double Window::my;

		Window::Window(const char *title, int width, int height) {
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!init()) 
				glfwTerminate();
			for (int i = 0; i < MAX_KEYS; i++)
				m_Keys[i] = false;
			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseButtons[i] = false;
			mx = 0;
			my = 0;
		}

		bool Window::init() {

			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window) {
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			return true;
		}
		
		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window)==1;
		}
	
		void Window::clear() const {

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {

			GLenum error = glGetError();
			if (errno != GL_NO_ERROR) {
				std::cout << "OpenGL error: " << error << std::endl;
			}

			glfwPollEvents();
//			glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glfwSwapBuffers(m_Window);
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::isKeyPressed(unsigned int keyCode) {
			//@TODO: LOG
			if (keyCode >= MAX_KEYS)
				return false;
			return m_Keys[keyCode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) {
			//@TODO: LOG
			if (button >= MAX_BUTTONS)
				return false;
			return m_MouseButtons[button];
		}

		void window_resize(GLFWwindow *window, int width, int height) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
			glViewport(0, 0, width, height);
		}
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Window*	win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			Window*	win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window*	win	 = (Window*) glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

	}
}