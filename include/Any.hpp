/**
 * @file Any.hpp
 * @author Soldatov Andrey (SoldatovAndreyWork@gmail.com)
 * @brief This file contains the Any class
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <string>
#include <utility>
#include <typeinfo>

//TODO: replace std::string with TAS::String
//TODO: std::swap() with TAS::swap()

namespace TAS {

/**
 * @brief This is a class for holding a value of any type(user-defined included)
 * 
 */
class Any{
    struct PlaceHolder {
        virtual ~PlaceHolder() {}
        virtual const std::type_info &type_info() const = 0;
        virtual PlaceHolder *clone() const = 0;
    };

    template<typename Type>
    struct Holder : public PlaceHolder {
        const Type m_held;

        Holder(const Type &val) : m_held(val) {}

        virtual const std::type_info &type_info() const {
            return typeid(Type);
        }

        virtual PlaceHolder *clone() const {
            return new Holder(m_held);
        }
    };
    
    PlaceHolder *m_content;

public:
    Any() : m_content(nullptr) {}
    ~Any() { delete m_content; }

    const std::type_info &type_info() const {
        return m_content ? m_content->type_info() : typeid(void);
    }

    Any(const Any &other) : m_content(other.m_content ? other.m_content->clone() : nullptr) {}

    template<typename Type>
    Any(const Type &val) : m_content(new Holder<Type>(val)) {}

    Any(const char *str) : m_content(new Holder<std::string>(str)) {}

    Any &swap(Any &rhs) {
        std::swap(m_content, rhs.m_content);
        return *this;
    }

    Any &operator=(const Any &rhs) {
        Any res = Any(rhs);
        return swap(res);
    }

    template<typename Type>
    Any &operator=(const Type &val) {
        Any res = Any(val);
        return swap(res);
    }

    /**
     * @brief Tries to cast internal content to desired type, if fails throws std::bad_cast()
     * 
     * @tparam Type 
     * @return Type 
     */
    template<typename Type>
    operator Type() {
        if(type_info() != typeid(Type)) throw std::bad_cast();
        return static_cast<Holder<Type> *>(m_content)->m_held; 
    }
};

}