#include "Rebound/Core/EntryPoint.h"
#include "Rebound/Layers/MainLayer.h"

class ReboundApplication : public Rebound::Application {
public:
    ReboundApplication() {
        Bounce::InitializeBounce();
        AddLayer(new Rebound::MainLayer());

    };
    ~ReboundApplication() {
        Bounce::ReleaseBounce();
    }
};

Rebound::Application *Rebound::CreateApplication() {
    return new ReboundApplication();
}
