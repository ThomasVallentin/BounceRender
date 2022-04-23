//
// Created by Thomas Vallentin on 10/04/2022.
//

#ifndef BOUNCE_TYPE_H
#define BOUNCE_TYPE_H

#include <string>
#include <vector>
#include <typeinfo>

namespace Rebound {

    class TypeRegistry;

    class Type {
    public:
        // Construct an empty invalid type
        Type() = default;

        // == DEFINITION ==

        template <class T>
        static void Define(const std::string &name) {
            Define(&typeid(T), name, {});
        }

        template <class T>
        static void Define(const std::string &name, const std::vector<Type> & bases) {
            Define(&typeid(T), name, bases);
        }

        // == TYPE SEARCHING ==

        // TODO(tvallentin): Might want to return const references to internally stored Types
        //                   instead of new objects
        template <class T>
        inline static Type Find() {
            return Type(FindByTypeId(&typeid(T)));
        }

        static Type FindByName(const std::string& name);

        // == INTROSPECTION ==

        inline bool IsValid() const {
            return m_typeData != nullptr;
        }

        std::string GetTypeName() const;

        bool IsA(const Type& other) const;

        template <class T>
        inline bool IsA() const {
            return IsA(Find<T>());
        }

        std::vector<Type> GetBases() const;
        std::vector<Type> GetDerived() const;

        // == OPERATORS ==

        inline bool operator ==(const Type& other) const { return other.m_typeData == m_typeData; }
        inline bool operator !=(const Type& other) const { return other.m_typeData != m_typeData; }
        inline operator bool() const { return IsValid(); }

    private:
        friend TypeRegistry;
        struct TypeData;

        explicit Type(TypeData* typeData) : m_typeData(typeData) {}

        static void Define(const std::type_info* info,
                           const std::string &name,
                           const std::vector<Type> & bases);

        static TypeData* FindByTypeId(const std::type_info* info);

        TypeData* m_typeData;
    };

    std::ostream& operator<<(std::ostream& out, const Type &type);

}

template <>
class std::hash<Rebound::Type> {
public:
    size_t operator()(const Rebound::Type &type) const {
        return std::hash<std::string>()(type.GetTypeName());
    }
};

#endif //BOUNCE_TYPE_H
