#include "dewpch.h"
#include "WindowsWindow.h"

#include "DEWEngine/Events/ApplicationEvent.h"
#include "DEWEngine/Events/MouseEvent.h"
#include "DEWEngine/Events/KeyEvent.h"

#include <glad/glad.h> // Modern OpenGL loader, must be included before GLFW to avoid conflicts


namespace DEWEngine {

	static bool s_GLFWInitialzied = false; // To ensure GLFW is initialized only once

	static void GLFWErrorCallback(int error, const char* description) {

		DEW_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback); // GLFWErrorCallback is a custom function to handle GLFW errors
			s_GLFWInitialzied = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

		// Make the created window the current context for OpenGL calls
			// The context holds all the info needed to render graphics on the window
			// OpenGL is thread specifc, so to draw a window from a specific thread, we need to make its context current
		glfwMakeContextCurrent(m_Window); 

		// Most platforms initially provide only OpenGL 1.1 (especially Windows). 
		// To use modern OpenGL features, you must load function pointers yourself at runtime.
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // Load OpenGL functions using glad
		DEW_CORE_ASSERT(status, "Failed to initialize Glad!"); // Check if glad was initialized successfully

		// Set the user pointer to access window data so we can use its Event callback functions
		glfwSetWindowUserPointer(m_Window, &m_Data); 
		SetVSync(true);


		// --- GLFW event callbacks ---
		// -- Window Events --
		// Window Resize Event
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {

			//Get the user pointer (which is our WindowData), returns void so we have to cast it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			
			WindowResizeEvent event(width, height);
			data.EventCallback(event); // Call the event callback with the resize event
		});

		// Window Close Event
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event); 
		});


		// -- Key Events --
		// Key Press Event
			// GLFW Key codes are GLFW specific, thus later in the event system we will convert them to DEWEngine key codes
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}

				case GLFW_REPEAT:
				{
					// GLFW doesnt provide a repeat count, but Win32 api does, hence we set it as 1 for now for future proofing
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}

		});

		// Key Type Event (for text input, like typing in a text box)
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});



		// -- Mouse Events --
		// Mouse Press Event
		glfwSetMouseButtonCallback(m_Window,[](GLFWwindow* window, int button, int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		// Mouse Scroll Event
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event); 

		});

		// Mouse Position Event
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			
		});
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
