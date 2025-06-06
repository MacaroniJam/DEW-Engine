#pragma once

// Will change based on the platform
#ifdef DEW_PLATFORM_WINDOWS

// A function which we will define somewhere else which will return our application
// CreateApplication will be implemented in the client
extern DEWEngine::Application* DEWEngine::CreateApplication();

// Creates our DEW Engine application for us
int main(int argc, char** argv) {

	auto app = DEWEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif
