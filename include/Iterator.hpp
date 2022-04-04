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

namespace TAS
{

typedef unsigned long int size_t;
typedef unsigned int ptrdiff_t;

/**
 * @brief Iterator is a pointer wrapper
 * 
 * @tparam T type of pointer
 */
template<typename T>
class Iterator {
    T *m_ptr;

public:
    Iterator() = delete;
    
    Iterator(T *ptr) : m_ptr(ptr) {}
    
    Iterator(const Iterator<T> &iterator) {
        m_ptr = iterator.m_ptr;
    }

    /**
     * @brief Advances iterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Retreats iterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Distance between two iterators
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(Iterator<T> const &rhs) {
        return rhs.m_ptr - m_ptr;
    }

    Iterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    Iterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    T &operator*() {
        return *m_ptr;
    }

    T const &operator*() const {
        return *m_ptr;
    }

    Iterator operator+(size_t n) const {
        return Iterator(m_ptr + n);
    }

    Iterator operator-(size_t n) const {
        return Iterator(m_ptr + n);
    }

    Iterator &operator+=(size_t n) {
        return next(n);
    }

    Iterator &operator-=(size_t n) {
        return prev(n);
    }

    Iterator &operator++() {
        return next();
    }

    Iterator &operator--() {
        return prev();
    }

    Iterator &operator++(int) {
        return next();
    }

    Iterator &operator--(int) {
        return prev();
    }

    bool operator==(Iterator<T> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(Iterator<T> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(Iterator<T> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator<(Iterator<T> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator>=(Iterator<T> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }

    bool operator<=(Iterator<T> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }
};

}