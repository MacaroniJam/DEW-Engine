#pragma once

#include "DEWEngine/Core.h"
#include "DEWEngine/Events/Event.h"

namespace DEWEngine
{
	// Base class for layers in the engine
	class DEW_API Layer
	{
	protected:
		std::string m_DebugName; //Layers should only have names for debugging purposes

	public:
		Layer(const std::string& debugName = "Layer"); // Constructor declaration with default parameter
		virtual ~Layer();

		virtual void OnAttach() {} // Push to layer stack
		virtual void OnDetach() {} // Pop from layer stack
		virtual void OnUpdate() {} // Called every frame
		virtual void OnEvent(Event& event) {} // Receives events 

		inline const std::string& GetName() const { return m_DebugName; }
	};
}


