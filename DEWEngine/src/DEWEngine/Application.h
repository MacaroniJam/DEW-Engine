#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"


namespace DEWEngine {

	class DEW_API Application
	{

	private:
		std::unique_ptr<Window> m_Window; //Unique pointer means only this class owns the window instance
		bool m_Running = true;

	public:
		Application();
		virtual ~Application();

		void Run();

	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

