#include <DEWEngine.h>

class SandBox : public DEWEngine::Application {

public:
	SandBox() {

	}

	~SandBox() {

	}

};

DEWEngine::Application* DEWEngine::CreateApplication() {
	return new SandBox();
}