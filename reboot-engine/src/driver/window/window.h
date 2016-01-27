#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

namespace reboot {
	namespace driver {

#define MAX_KEYS	1024
#define MAX_BUTTONS 24

		class Window
		{
		private:
			friend struct GLFWwindow;

			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_MouseGrabbed;
			static bool m_Keys[MAX_KEYS];
			static bool m_MouseButtons[MAX_BUTTONS];
			static double mx, my, dx, dy;
		public:
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline int getWidht() const { return m_Width; }
			inline int getHeight() const { return m_Height; }
			inline void getMousePosition(double& x, double& y) const { x = mx; y = my; }
			inline void getMouseMove(double& x, double& y) const { x = dx; y = dy; }

			const inline bool Window::isGrabbed() { return m_MouseGrabbed;}

			void setMouseGrabbed(bool grabbed);

			static bool isKeyPressed(unsigned int keyCode);
			static bool isMouseButtonPressed(unsigned int button);
		private:
			bool init();
			friend static void window_resize(GLFWwindow *window, int width, int height);
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		};
	}
}