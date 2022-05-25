#include "Rebound/Core/EntryPoint.h"
#include "Rebound/Layers/MainLayer.h"

#include <BounceRender/Core/Scene.h>

class ReboundApplication : public Rebound::Application {

public:
    ReboundApplication() {
        Bounce::InitializeBounce();
        auto scene = Bounce::Scene();

        AddLayer(new Rebound::MainLayer());

    };
    ~ReboundApplication() = default;
};

Rebound::Application *Rebound::CreateApplication() {
    return new ReboundApplication();
}
