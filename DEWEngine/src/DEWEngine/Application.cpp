#include "dewpch.h"
#include "Application.h"

#include "DEWEngine/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace DEWEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) // Macro to bind event functions to the application instance

	Application* Application::s_Instance = nullptr; // no active instance of Application yet

	Application::Application() {
		// Initialize the application
		DEW_CORE_ASSERT(!s_Instance, "Application already exists!"); // If not null, an instance already exists
		s_Instance = this; // Set singleton instance to current instance

		m_Window = std::unique_ptr<Window>(Window::Create()); // Deletes the window when Application terminates
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

	}

	Application::~Application() {
		// Clean up resources
	}

	void Application::PushLayer(Layer* layer) {
		// Add a layer to the application
		m_LayerStack.PushLayer(layer);
		layer->OnAttach(); // Call OnAttach for the layer to initialize it
	}

	void Application::PushOverlay(Layer* layer) {
		// Add an overlay to the application
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
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