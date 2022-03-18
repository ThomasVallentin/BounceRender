//
// Created by Thomas Vallentin on 17/03/2022.
//

#include "LayerStack.h"

Bounce::Gui::LayerStack::~LayerStack() {
    for (Layer* layer : m_layers)
        delete layer;
}

void Bounce::Gui::LayerStack::AddLayer(Bounce::Gui::Layer *layer) {
    m_layers.emplace_back(layer);
    layer->OnAttach();
}

void Bounce::Gui::LayerStack::RemoveLayer(Bounce::Gui::Layer *layer) {
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if (it != m_layers.end())
        m_layers.erase(it);

    layer->OnDetach();
}

