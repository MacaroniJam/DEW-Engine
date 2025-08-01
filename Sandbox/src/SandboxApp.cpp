#include <DEWEngine.h>

class ExampleLayer : public DEWEngine::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	void OnUpdate() override {
		DEW_INFO("ExampleLayer::Update");
	}

	void OnEvent(DEWEngine::Event& event) override {
		DEW_TRACE("{0}", event);
	}
};

class SandBox : public DEWEngine::Application {

public:
	SandBox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new DEWEngine::ImGuiLayer());
	}

	~SandBox() {

	}

};

DEWEngine::Application* DEWEngine::CreateApplication() {
	return new SandBox();
}