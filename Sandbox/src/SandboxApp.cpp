#include <DEWEngine.h>

class ExampleLayer : public DEWEngine::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	void OnUpdate() override {

		if (DEWEngine::Input::IsKeyPressed(DEW_KEY_TAB))
			DEW_TRACE("Tab key is pressed! (poll)");
	}

	void OnEvent(DEWEngine::Event& event) override {
		//DEW_TRACE("{0}", event);

		if (event.GetEventType() == DEWEngine::EventType::KeyPressed) {
			DEWEngine::KeyPressedEvent& e = (DEWEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == DEW_KEY_TAB)
				DEW_TRACE("Tab key was pressed (event)!");

			DEW_TRACE("{0}", (char)e.GetKeyCode());
		}
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