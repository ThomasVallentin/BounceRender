//
// Created by Thomas Vallentin on 10/06/2022.
//

#ifndef RBND_SCENENOTIFIER_H
#define RBND_SCENENOTIFIER_H

#include "Rebound/Core/Notifier.h"

#include <set>

namespace Rebound {

    class Scene;
    class Entity;


    enum class SceneNoticeType {
        EntitiesChanged = 0,
        EntitiesAdded,
        EntitiesRemoved
    };


    class SceneNotice : public Notice {
    public:
        explicit SceneNotice(const Scene *scene) : m_scene(scene) {}

        virtual SceneNoticeType GetType() const = 0;
        inline std::string GetTypeName() const override { return "SceneNotice"; }

    protected:
        const Scene *m_scene;
    };

    typedef std::pair<Entity, std::set<std::string>> AffectedAttribute;

    // TODO: For the moment every attribute will have its own notice. This is a basic
    //       implementation, the Scenes should be able to notify multiple attributes
    //       from multiple Entities at once.
    class EntityChangedNotice : public SceneNotice {
    public:
        EntityChangedNotice(const Scene *scene, const AffectedAttribute &affectedAttribute) :
                SceneNotice(scene),
                m_affectedAttribute(affectedAttribute) {}

        inline std::string GetTypeName() const override { return "SceneNoticeType::EntitiesChanged"; }
        inline static SceneNoticeType GetStaticType() { return SceneNoticeType::EntitiesChanged; }
        inline virtual SceneNoticeType GetType() const override { return GetStaticType(); }

        const AffectedAttribute &GetAffectedAttribute() const { return m_affectedAttribute; }

    private:
        AffectedAttribute m_affectedAttribute;
    };

    class SceneNotifier {
    public:
        inline static void NotifyEntityChanged(Scene *scene,
                                               const AffectedAttribute &affectedAttribute) {
            Notifier<Scene*>::Notify(scene,
                                     new EntityChangedNotice(scene, {affectedAttribute}));
        }
    };

}

#endif //RBND_SCENENOTIFIER_H
