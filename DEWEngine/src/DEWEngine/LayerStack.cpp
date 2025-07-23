#include "dewpch.h"
#include "LayerStack.h"

namespace DEWEngine
{
	LayerStack::LayerStack() {
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	//Layers are inserted at the first half of the vector
	void LayerStack::PushLayer(Layer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	//Overlays are inserted at the second half of the vector as we want to render them last
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}


	// The PopLayer and Overlay methods arent responsible for deleting the layer from memory
	// We want the keep the LayerStack during the lifetime of the application, 
	// hence once the application is done, the layerstack will delete all layers
	//This also allows us to undo and redo layers if needed
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}