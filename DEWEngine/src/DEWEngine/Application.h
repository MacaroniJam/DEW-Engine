#pragma once
#include "Core.h"


namespace DEWEngine {

	class DEW_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();

	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

