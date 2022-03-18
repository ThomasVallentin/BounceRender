#include "App/EntryPoint.h"
#include "Layers/UILayer.h"


class BounceGui : public Bounce::Gui::Application {
public:
    BounceGui() {
        AddLayer(new UILayer());
    };
    ~BounceGui() = default;
};

Bounce::Gui::Application *Bounce::Gui::CreateApplication() {
    return new BounceGui();
}
