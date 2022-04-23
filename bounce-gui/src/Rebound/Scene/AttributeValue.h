//
// Created by Thomas Vallentin on 31/03/2022.
//

#ifndef TEST_ATTRIBUTEVALUE_H
#define TEST_ATTRIBUTEVALUE_H

#include <boost/type_index.hpp>

#include <unordered_map>
#include <any>
#include <iostream>


namespace Rebound {


    class AttributeValue {
    public:
        AttributeValue() = default;

        // Creates a new empty AttributeValue
        template<typename T>
        static AttributeValue New() {
            AttributeValue at;
            at.m_value = std::make_any<T>();
            return at;
        }

        // Cast an existing value to an AttributeValue
        template<typename T>
        static AttributeValue Cast(T value) {
            AttributeValue at;
            at.m_value = std::make_any<T>(value);
            return at;
        }

        // Change the internal value of the AttributeValue
        template<typename T>
        inline T Set(T &value) {
            return m_value = std::make_any<T>(value);
        }

        // Returns whether the internal value is of the given Type
        template<typename T>
        inline bool Is() {
            return typeid(T) == m_value.type();
        }

        // Returns back the internal value if the given type matches the internal type
        template<typename T>
        inline bool As(T &value) {
            if (!Is<T>()) {
                return false;
            }
            value = std::any_cast<T>(m_value);
            return true;
        }

        std::string GetTypeName() const {
            return boost::typeindex::stl_type_index(m_value.type()).pretty_name();
        }

    private:
        std::any m_value;
    };

}

#endif //TEST_ATTRIBUTEVALUE_H
