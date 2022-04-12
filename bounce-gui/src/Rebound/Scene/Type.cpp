//
// Created by Thomas Vallentin on 10/04/2022.
//

#include "Type.h"

#include <boost/type_index.hpp>

#include <iostream>
#include <string>
#include <unordered_map>
#include <typeinfo>

namespace Rebound {

    struct Type::TypeData {
        const std::string name;
        const std::type_info * typeInfo;

        std::vector<Type> bases;
        std::vector<Type> derived;
    };

    class TypeRegistry {
    public:
        TypeRegistry(const TypeRegistry&) = delete;

        Type::TypeData *Find(const std::type_info *info) {
            auto it = m_typeinfoToTypeData.find(info);
            if (it != m_typeinfoToTypeData.end()) {
                return it->second;
            }

            return nullptr;
        }

        Type::TypeData *Find(const std::string &name) {
            auto it = m_nameToTypeData.find(name);
            if (it != m_nameToTypeData.end()) {
                return it->second;
            }

            return nullptr;
        }

        static TypeRegistry& Get() {
            return s_instance;
        }

        Type::TypeData *NewTypeData(const std::string &name, const std::type_info* typeInfo) {
            auto *typeData = new Type::TypeData{name, typeInfo};
            m_nameToTypeData[name] = typeData;
            m_typeinfoToTypeData[typeInfo] = typeData;

            return typeData;
        }

    private:
        TypeRegistry() = default;

        std::unordered_map<std::string, Type::TypeData*> m_nameToTypeData;
        std::unordered_map<const std::type_info*, Type::TypeData*> m_typeinfoToTypeData;

        static TypeRegistry s_instance;
    };

    // Define singleton instance
    TypeRegistry TypeRegistry::s_instance;

    void Type::Define(const std::type_info *info, const std::vector<Type> &bases) {
        if (FindByTypeId(info))
            return;

        auto &registry = TypeRegistry::Get();

        // Create new Type & TypeData
        TypeData *newTypeData = registry.NewTypeData(
                boost::typeindex::stl_type_index(*info).pretty_name(), info);
        Type newType(newTypeData);

        // Set bases to new type
        newTypeData->bases = bases;

        // Add new type as derived of bases
        for (auto& base : bases)
            base.m_typeData->derived.push_back(newType);
    }

    Type::TypeData* Type::FindByTypeId(const std::type_info *info) {
        return TypeRegistry::Get().Find(info);
    }

    Type Type::FindByName(const std::string &name) {
        return Type(TypeRegistry::Get().Find(name));
    }

    std::string Type::GetTypeName() const {
        return m_typeData->name;
    }

    bool Type::IsA(const Type& other) const {
        // Same type -> True
        if (other == *this)
            return true;

        // Invalid types -> False
        if (!other.IsValid() || !this->IsValid())
            return false;

        for (const auto &base : m_typeData->bases) {
            if (base == other)
                return true;

            if (base.IsA(other))
                return true;
        }

        return false;

    }

    std::vector<Type> Type::GetBases() const {
        return m_typeData->bases;
    }

    std::vector<Type> Type::GetDerived() const {
        return m_typeData->derived;
    }

    std::ostream& operator<<(std::ostream& out, const Type &type) {
        return out << "Type(" << type.GetTypeName() << ")";
    }

}
