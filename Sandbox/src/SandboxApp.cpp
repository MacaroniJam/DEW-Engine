#include <DEWEngine.h>

class SandBox : public DEWEngine::Application {

public:
	SandBox() {

	}

	~SandBox() {

	}

};

DEWEngine::Application* CreateApplication() {
	return new SandBox();
}