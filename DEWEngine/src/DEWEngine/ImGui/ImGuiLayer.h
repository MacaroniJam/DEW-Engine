#pragma once

#include "DEWEngine/Layer.h"

#include "DEWEngine/Events/ApplicationEvent.h"
#include "DEWEngine/Events/MouseEvent.h"
#include "DEWEngine/Events/KeyEvent.h"


namespace DEWEngine {

	class DEW_API ImGuiLayer : public Layer {

	private:
		// Variables
		float m_Time = 0.0f; // Time since the application started or previous frame time

		// Functions:
		//	Mouse Functions
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		//	Keyboard Functions
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e); // Types an actual character when keycode is pressed

		//	Window Functions
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	};
}
