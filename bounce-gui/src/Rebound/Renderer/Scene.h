//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_RENDERSCENE_H
#define RBND_RENDERSCENE_H

#include "Item.h"

#include "Rebound/Scene/Entity.h"


namespace Rebound {

    class RenderScene {
    public:
        RenderScene() = default;

        void AddEntity(const Entity &entity);
        void RemoveEntity(const Entity &entity);

        inline void Clear() { m_items.clear(); }
        inline void Invalidate(const Entity &entity) const;
        void Update();

        void Submit();

        inline std::shared_ptr<Material> GetDefaultMaterial() {
            return m_defaultMaterial;
        }
        inline void SetDefaultMaterial(std::shared_ptr<Material> material) {
            m_defaultMaterial = std::move(material);
        }

    private:
        RenderItem* GetItem(const Entity &entity) const;
        void UpdateItem(const Entity &entity, RenderItem* item);

        std::unordered_map<Entity, RenderItem*> m_items;
        std::shared_ptr<Material> m_defaultMaterial;
    };

}

#endif //RBND_RENDERSCENE_H
