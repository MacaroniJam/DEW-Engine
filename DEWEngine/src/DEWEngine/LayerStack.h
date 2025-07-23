#pragma once

#include "DEWEngine/Core.h"
#include "Layer.h"

#include <vector>

namespace DEWEngine {

	class DEW_API LayerStack
	{
	private:
		// We are using a vector to store the layers as it allows for dynamic resizing and reverse iteration for every frame updates.
		// In addition we will be inserting layers at any position, thus not traditionally stacking them.
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert; //Iterator keeps track of only LAYERS, not OVERLAYS

	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);

		// Overlays are layers that are always on top of the stack and do not get removed when a new layer is pushed.
		void PushOverlay(Layer* overlay); 

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	};
}



