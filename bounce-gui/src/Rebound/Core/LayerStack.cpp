//
// Created by Thomas Vallentin on 17/03/2022.
//

#include "LayerStack.h"

Rebound::LayerStack::~LayerStack() {
    for (Layer* layer : m_layers)
        delete layer;
}

void Rebound::LayerStack::AddLayer(Rebound::Layer *layer) {
    m_layers.emplace_back(layer);
    layer->OnAttach();
}

void Rebound::LayerStack::RemoveLayer(Rebound::Layer *layer) {
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if (it != m_layers.end())
        m_layers.erase(it);

    layer->OnDetach();
}

