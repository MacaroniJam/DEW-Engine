#pragma once

#include "DEWEngine/Layer.h"
namespace DEWEngine {

	class DEW_API ImGuiLayer : public Layer {

	private:
		float m_Time = 0.0f; // Time since the application started or previous frame time

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	};
}
