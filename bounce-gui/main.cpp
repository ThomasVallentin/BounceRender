#include "App/EntryPoint.h"
#include "Layers/UILayer.h"
#include "Layers/RenderLayer.h"


class BounceGui : public Bounce::Gui::Application {
public:
    BounceGui() {
//        AddLayer(new Bounce::Gui::UILayer());
        AddLayer(new Bounce::Gui::RenderLayer());
    };
    ~BounceGui() = default;
};

Bounce::Gui::Application *Bounce::Gui::CreateApplication() {
    return new BounceGui();
}
