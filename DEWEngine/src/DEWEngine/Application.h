#pragma once
#include "Core.h"

#include "Window.h"
#include "DEWEngine/LayerStack.h"
#include "DEWEngine/Events/Event.h"
#include "DEWEngine/Events/ApplicationEvent.h"


namespace DEWEngine {

	class DEW_API Application
	{

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; //Unique pointer means only this class owns the window instance
		bool m_Running = true;

		LayerStack m_LayerStack;

	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

