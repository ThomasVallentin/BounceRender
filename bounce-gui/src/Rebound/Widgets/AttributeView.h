//
// Created by Thomas Vallentin on 12/04/2022.
//

#ifndef BOUNCE_ATTRIBUTEVIEW_H
#define BOUNCE_ATTRIBUTEVIEW_H

#include <map>
#include "Rebound/Core/Widget.h"
#include "Rebound/Scene/Entity.h"


namespace Rebound {

#define BIND_ADD_CHANNEL_FN(Func) [this](Entity *PH1, const std::string &PH2, AttributeValue &PH3) { Func(PH1, PH2, PH3); };

    class AttributeViewWidget : public Widget {
    public:
        AttributeViewWidget();

        void PreRender() override;
        void Render() override;
        void PostRender() override;

        inline void SetEntity(Entity* entity) { m_entity = entity; }

    private:
        using AddChannelFn = std::function<void(Entity *, const std::string &, AttributeValue &)>;

        inline void NewAddChannelFn(const std::string& typeName, AddChannelFn fn) {
            m_addChannelFunctions[typeName] = fn;
        }

        AddChannelFn FindAddChannelFn(const std::string& typeName);
        void AddVec3Channel(Entity *entity,
                            const std::string &name,
                            AttributeValue &atValue);
        void AddUnsupportedChannel(Entity *entity,
                                   const std::string &name,
                                   const AttributeValue &atValue) const;

        Entity *m_entity;

        std::map<std::string, AddChannelFn> m_addChannelFunctions;

        bool m_showUnsupportedAttributes = false;
        float m_textValueSplit = 80.0f;
        float m_textValueSpacing = 8.0f;
    };

}


#endif //BOUNCE_ATTRIBUTEVIEW_H
