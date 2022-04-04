//
// Created by Margaux TAMIC on 25/03/2022.
//

#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <unordered_map>
#include <any>
#include <functional>


namespace Rebound {

    class Scene;

    class AttributeValue;

    typedef uint32_t EntityDataHandle;
    typedef std::pair<std::string, AttributeValue> AttributeSpec;
    typedef std::function<void(const EntityDataHandle& handle)> DataTraversalFunc;

    class AttributeView {
    public:
        AttributeView() = default;

        inline std::vector<AttributeSpec>::iterator begin() { return m_attributesPtr->begin(); }

        inline std::vector<AttributeSpec>::iterator end() { return m_attributesPtr->end(); }

        inline std::vector<AttributeSpec>::const_iterator
        begin() const { return m_attributesPtr->begin(); }

        inline std::vector<AttributeSpec>::const_iterator
        end() const { return m_attributesPtr->end(); }

    private:
        std::vector<AttributeSpec> *m_attributesPtr;
    };


    class SceneData {
    public:
        SceneData(const SceneData &) = delete;

        // == HANDLE CREATION ==

        template<class EntityType>
        EntityDataHandle CreateHandle(const std::string &name) {
            EntityDataHandle handle = m_data.size() + 1;  // 0 is keeped for the empty handles
            m_data[handle] = EntityData{name, &typeid(EntityType)};
            return handle;
        }

        // == NAMING ==

        std::string GetName(const EntityDataHandle &entity);

        void SetName(const EntityDataHandle &entity,
                     const std::string &name);

        std::string GetTypeName(const EntityDataHandle &entity);

        // == ATTRIBUTES ==

        bool GetAttribute(const EntityDataHandle &entity,
                          const std::string &name,
                          AttributeValue &outData) const;

        bool SetAttribute(const EntityDataHandle &entity,
                          const std::string &name,
                          AttributeValue value);

        // == HIERARCHY ==

        void Traverse(const EntityDataHandle &entity,
                      const DataTraversalFunc &func);

        EntityDataHandle GetParent(const EntityDataHandle &entity) const;
        uint32_t GetChildCount(const EntityDataHandle &entity) const;
        EntityDataHandle GetChild(const EntityDataHandle &entity,
                                  const uint32_t& index) const;
        bool AddChild(const EntityDataHandle &parent,
                      const EntityDataHandle &entity);
        bool RemoveChild(const EntityDataHandle &parent,
                         const EntityDataHandle &entity);

        std::vector<EntityDataHandle> GetRootHandles() const;

    private:
        struct EntityData {
            std::string name;
            const std::type_info *type;
            std::vector<AttributeSpec> attributes;

            EntityDataHandle parent;
            std::vector<EntityDataHandle> children;
        };

        typedef std::unordered_map<std::string, AttributeValue> AttributeMap;
        typedef std::unordered_map<EntityDataHandle, EntityData> DataTable;

        const SceneData::EntityData *SceneData::GetEntityData(const EntityDataHandle &entity) const;

        SceneData::EntityData *SceneData::GetEntityData(const EntityDataHandle &entity);

    private:
        friend Scene;

        SceneData() = default;

        DataTable m_data;
    };

}


#endif //TEST_DATA_H
