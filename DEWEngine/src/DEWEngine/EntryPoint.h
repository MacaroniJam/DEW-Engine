#pragma once

// Will change based on the platform
#ifdef DEW_PLATFORM_WINDOWS

// A function which we will define somewhere else which will return our application
// CreateApplication will be implemented in the client
extern DEWEngine::Application* DEWEngine::CreateApplication();

// Creates our DEW Engine application for us
int main(int argc, char** argv) {

	DEWEngine::Log::Init(); // Temporary line, Initialize the logging system
	DEW_CORE_WARN("Intialized Log!"); // Log a warning message

	int a = 5; // Example variable
	DEW_INFO("Hello! Var={0}", a); // Log an info message

	auto app = DEWEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif
