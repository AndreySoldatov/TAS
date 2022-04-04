/**
 * @file Tuple.hpp
 * @author Soldatov Andrey (SoldatovAndreyWork@gmail.com)
 * @brief This file contains the Tuple class
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <Any.hpp>
#include <Array.hpp>

namespace TAS {

/**
 * @brief Tuple class represents a containter of constant size
 * with arguments of any type.
 * 
 * @tparam Size - size of the tuple
 */
template<size_t Size>
class Tuple{
    Array<Any, Size> m_data{};

    void recursiveFill(size_t index) {
        if(index == Size) return;
        throw std::out_of_range("too few args in tuple construction!");
    }

    template<typename Head, typename... Tail>
    void recursiveFill(size_t index, Head const &head, const Tail&... tail) {
        if(index >= Size) throw std::out_of_range("too much args in tuple construction!");
        m_data[index] = head;
        recursiveFill(index + 1, tail...);
    }

public:
    Tuple() = default;

    /**
     * @brief Construct a new Tuple object. If argument count is too small, or too big, throws std::out_of_range
     * 
     * @tparam Types - Tuple construction types
     * @param val  - Tuple construction values
     */
    template<typename... Types>
    Tuple(const Types&... val) {
        recursiveFill(0, val...);
    }

    Tuple(Tuple const &rhs) {
        m_data = rhs.m_data;
    }

    Tuple &operator=(Tuple const &rhs) {
        m_data = rhs.m_data;
        return *this;
    }
    
    /**
     * @brief if out of bounds throws std::out_of_range
     * 
     * @param index 
     * @return Any& 
     */
    Any &operator[](size_t index) {
        if(index >= Size) throw std::out_of_range("tuple out of bounds");
        return m_data[index];
    }

    /**
     * @brief if out of bounds throws std::out_of_range
     * 
     * @param index 
     * @return Any const& 
     */
    Any const &operator[](size_t index) const {
        if(index >= Size) throw std::out_of_range("tuple out of bounds");
        return m_data[index];
    }
};

}