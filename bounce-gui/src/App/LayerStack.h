//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_LAYERSTACK_H
#define BOUNCE_LAYERSTACK_H


#include "Layer.h"

namespace Bounce::Gui {

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void AddLayer(Layer* layer);
        void RemoveLayer(Layer* layer);

        inline std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        inline std::vector<Layer*>::iterator end() { return m_layers.end(); }

    private:
        std::vector<Layer*> m_layers;
    };

}


#endif //BOUNCE_LAYERSTACK_H
