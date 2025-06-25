#include "dewpch.h"
#include "WindowsWindow.h"

namespace DEWEngine {

	static bool s_GLFWInitialzied = false; // To ensure GLFW is initialized only once

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	void WindowsWindow::Init(const WindowProps& props) {

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		DEW_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialzied) {
			// If it hasn't been initialized yet, initialize GLFW
			int success = glfwInit();
			DEW_CORE_ASSERT(success, "Could not initialize GLFW!");
			
			s_GLFWInitialzied = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

		// Make the created window the current context for OpenGL calls
			// The context holds all the info needed to render graphics on the window
			// OpenGL is thread specifc, so to draw a window from a specific thread, we need to make its context current
		glfwMakeContextCurrent(m_Window); 

		// Set the user pointer to access window data so we can use its Event callback functions
		glfwSetWindowUserPointer(m_Window, &m_Data); 
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents(); // Poll for events (like key presses, mouse movements, etc.)

		// Swap the front and back buffers to display the rendered content
			// Front buffer: the one currently being displayed
			// Back buffer: the frame thats currently being drawn
		glfwSwapBuffers(m_Window); 
	}

	void WindowsWindow::SetVSync(bool enabled) {

		if (enabled) {
			glfwSwapInterval(1); //Enable VSync, waits for one screen refresh before swapping buffers
		}
		else {
			glfwSwapInterval(0); //Disable VSync, swaps buffers immediately
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}
