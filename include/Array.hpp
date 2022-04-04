/**
 * @file Array.hpp
 * @author Soldatov Andrey (SoldatovAndreyWork@gmail.com)
 * @brief This file contains the Array class
 * @version 0.1
 * @date 2022-04-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <initializer_list>
#include <stdexcept>

//TODO: add TAS::Iterator

namespace TAS
{

typedef long unsigned int size_t;

/**
 * @brief constant sized Array of orbitrary type
 * 
 * @tparam T type
 * @tparam Size size
 */
template<typename T, size_t Size>
class Array {
    T m_data[Size]{};

public:
    /**
     * @brief Construct a new Array object from std::initalizer_list
     * 
     * @param val 
     */
    Array(std::initializer_list<T>const &val) {
        //FIXME: more delightful message pls
        if(val.size() != Size) throw std::out_of_range("Args");
        std::copy(val.begin(), val.begin() + Size, m_data);
    }

    Array() = default;
    ~Array() = default;

    /**
     * @brief if out of range throws std::out_of_range
     * 
     * @param index 
     * @return T& 
     */
    T &at(size_t index) {
        if(index >= Size) throw std::out_of_range("Index is out of range");
        return m_data[index];
    }

    /**
     * @brief if out of range throws std::out_of_range
     * 
     * @param index 
     * @return T& 
     */
    const T &at(size_t index) const {
        if(index >= Size) throw std::out_of_range("Index is out of range");
        return m_data[index];
    }

    /**
     * @brief WARNING: does not throw if exceedes
     * 
     * @param index 
     * @return T& 
     */
    T &operator[](size_t index) {
        return m_data[index];
    }

    /**
     * @brief WARNING: does not throw if exceedes
     * 
     * @param index 
     * @return T& 
     */
    const T &operator[](size_t index) const {
        return m_data[index];
    }
    
    /**
     * @brief raw data ptr
     * 
     * @return T* 
     */
    T *data() {
        return m_data;
    }

    const T &front() const {
        return m_data[0];
    }

    const T &back() const {
        return m_data[Size - 1];
    }

    bool empty() const {
        return !Size;
    }

    size_t size() const {
        return Size;
    }

    size_t max_size() const {
        return size();
    }

    //FIXME: CHANGE TO TAS::Iterator
    T *begin() {
        return m_data;
    }

    //FIXME: CHANGE TO TAS::Iterator
    const T *cbegin() const {
        return m_data;
    }

    //FIXME: CHANGE TO TAS::Iterator
    T *end() {
        return m_data + Size;
    }

    //FIXME: CHANGE TO TAS::Iterator
    const T *cend() const {
        return m_data + Size;
    }

    //FIXME: IMPLEMENT REVERSE ITERATORS (rbegin(), rend(), crbegin(), crend())
};

} // namespace TAS



