#include "dewpch.h"
#include "Application.h"


#include "DEWEngine/Log.h"

#include <GLFW/glfw3.h>

namespace DEWEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) // Macro to bind event functions to the application instance

	Application::Application() {
		// Initialize the application

		m_Window = std::unique_ptr<Window>(Window::Create()); // Deletes the window when Application terminates
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {
		// Clean up resources
	}

	void Application::PushLayer(Layer* layer) {
		// Add a layer to the application
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		// Add an overlay to the application
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e) {
		//Handle Events
		EventDispatcher dispatcher(e);

		//dispatcher.Dispatch<type>(function)
			//If the event is a certian type, call the specified function
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));


		//Layers are handled in reverse order
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {

			(*--it)->OnEvent(e);

			if (e.Handled) break; // If the event is handled, stop processing further layers
		}
	}

	void Application::Run() {
		// Main loop of the application
		while (m_Running) {
			glClearColor(1, 0, 1, 1); // Set clear color to pink
			glClear(GL_COLOR_BUFFER_BIT); // Clear the screen using the specified color

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(); // Update each layer in the stack
			}
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;
	}

	
}