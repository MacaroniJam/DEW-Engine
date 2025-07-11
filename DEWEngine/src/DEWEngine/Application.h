#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "DEWEngine/Events/ApplicationEvent.h"
#include "Window.h"


namespace DEWEngine {

	class DEW_API Application
	{

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; //Unique pointer means only this class owns the window instance
		bool m_Running = true;

	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

