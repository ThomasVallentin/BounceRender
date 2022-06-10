#include "Rebound/Core/EntryPoint.h"
#include "Rebound/Layers/MainLayer.h"

class ReboundApplication : public Rebound::Application {

public:
    ReboundApplication() {
        AddLayer(new Rebound::MainLayer());

    };
    ~ReboundApplication() = default;
};

Rebound::Application *Rebound::CreateApplication() {
    return new ReboundApplication();
}
