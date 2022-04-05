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
#include <functional>

//TODO: add TAS::ReverseIterator
//TODO: change std::function with TAS::Function

namespace TAS
{

//Forwards
template<typename T>
class ArrayIterator;

template<typename T>
class ConstArrayIterator;

template<typename T>
class ReverseArrayIterator;

template<typename T>
class ConstReverseArrayIterator;
//Forwards

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
     * @brief Construct a new Array object by filling it with val
     * 
     * @param val 
     */
    Array(T const &val) {
        fill(val);
    }

    /**
     * @brief Fills array with value of type T
     * 
     * @param val 
     */
    void fill(T const &val) {
        for (ArrayIterator i = begin(); i < end(); i++)
        {
            *i = val;
        }
    }

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

    ArrayIterator<T> begin() {
        return m_data;
    }

    ConstArrayIterator<T> cbegin() const {
        return m_data;
    }

    ReverseArrayIterator<T> rbegin() {
        return (m_data + Size - 1);
    }

    ConstReverseArrayIterator<T> crbegin() const {
        return (m_data + Size - 1);
    }

    ArrayIterator<T> end() {
        return m_data + Size;
    }

    ConstArrayIterator<T> cend() const {
        return m_data + Size;
    }

    ReverseArrayIterator<T> rend() {
        return m_data - 1;
    }

    ConstReverseArrayIterator<T> crend() const {
        return m_data - 1;
    }

    /**
     * @brief Applies Lambda that is not modifying the array
     * 
     * @param f 
     */
    void forEach(std::function<void(T const &)> const &f) const {
        for (ConstArrayIterator i = cbegin(); i < cend(); i++)
        {
            f(*i);
        }
    }

    /**
     * @brief Applies Lambda that is modifying the referce to the array element
     * 
     * @param f 
     */
    void transformReference(std::function<void(T &)> const &f) {
        for (ArrayIterator i = begin(); i < end(); i++)
        {
            f(*i);
        }
    }

    /**
     * @brief Applies Lambda that returns copy of modified element
     * 
     * @param f 
     */
    void transformAndCopy(std::function<T(T const &)> const &f) {
        for (ArrayIterator i = begin(); i < end(); i++)
        {
            *i = f(*i);
        }
    }

    bool operator==(Array<T, Size> const &rhs) const {
        for (size_t i = 0; i < Size; i++)
        {
            if(m_data[i] != rhs[i]) return false;
        }
        return true;
    }

    //TODO: IMPLEMENT REVERSE ITERATORS (rbegin(), rend(), crbegin(), crend())
};


template<typename T>
class ArrayIterator {
    T *m_ptr;

public:
    ArrayIterator() = delete;
    
    ArrayIterator(T *ptr) : m_ptr(ptr) {}
    
    ArrayIterator(const ArrayIterator<T> &ArrayIterator) {
        m_ptr = ArrayIterator.m_ptr;
    }

    /**
     * @brief Advances ArrayIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Retreats ArrayIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Distance between two ArrayIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(ArrayIterator<T> const &rhs) const {
        return rhs.m_ptr - m_ptr;
    }

    ArrayIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    ArrayIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    T &operator*() const {
        return *m_ptr;
    }

    ArrayIterator operator+(size_t n) const {
        return ArrayIterator(m_ptr + n);
    }

    ArrayIterator operator-(size_t n) const {
        return ArrayIterator(m_ptr - n);
    }

    ptrdiff_t operator-(ArrayIterator<T> const &rhs) const {
        return disctance(rhs);
    }

    ArrayIterator &operator+=(size_t n) {
        return next(n);
    }

    ArrayIterator &operator-=(size_t n) {
        return prev(n);
    }

    ArrayIterator &operator++() {
        return next();
    }

    ArrayIterator &operator--() {
        return prev();
    }

    ArrayIterator operator++(int) {
        ArrayIterator ai{m_ptr};
        next();
        return ai;
    }

    ArrayIterator operator--(int) {
        ArrayIterator ai{m_ptr};
        prev();
        return ai;
    }

    bool operator==(ArrayIterator<T> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(ArrayIterator<T> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(ArrayIterator<T> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator<(ArrayIterator<T> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator>=(ArrayIterator<T> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }

    bool operator<=(ArrayIterator<T> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }
};

template<typename T>
class ConstArrayIterator {
    T const *m_ptr;

public:
    ConstArrayIterator() = delete;
    
    ConstArrayIterator(T const *ptr) : m_ptr(ptr) {}
    
    ConstArrayIterator(const ConstArrayIterator<T> &constArrayIterator) {
        m_ptr = constArrayIterator.m_ptr;
    }

    ConstArrayIterator(const ArrayIterator<T> &arrayIterator) {
        m_ptr = arrayIterator.m_ptr;
    }

    /**
     * @brief Advances ConstArrayIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Retreats ConstArrayIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Distance between two ConstArrayIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(ConstArrayIterator<T> const &rhs) const {
        return rhs.m_ptr - m_ptr;
    }

    ConstArrayIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    ConstArrayIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    T const &operator*() const {
        return *m_ptr;
    }

    ConstArrayIterator operator+(size_t n) const {
        return ConstArrayIterator(m_ptr + n);
    }

    ConstArrayIterator operator-(size_t n) const {
        return ConstArrayIterator(m_ptr - n);
    }

    ptrdiff_t operator-(ConstArrayIterator<T> const &rhs) const {
        return disctance(rhs);
    }

    ConstArrayIterator &operator+=(size_t n) {
        return next(n);
    }

    ConstArrayIterator &operator-=(size_t n) {
        return prev(n);
    }

    ConstArrayIterator &operator++() {
        return next();
    }

    ConstArrayIterator &operator--() {
        return prev();
    }

    ConstArrayIterator operator++(int) {
        ConstArrayIterator cai{m_ptr};
        next();
        return cai;
    }

    ConstArrayIterator operator--(int) {
        ConstArrayIterator cai{m_ptr};
        prev();
        return cai;
    }

    bool operator==(ConstArrayIterator<T> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(ConstArrayIterator<T> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(ConstArrayIterator<T> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator<(ConstArrayIterator<T> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator>=(ConstArrayIterator<T> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }

    bool operator<=(ConstArrayIterator<T> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }
};





template<typename T>
class ReverseArrayIterator {
    T *m_ptr;

public:
    ReverseArrayIterator() = delete;
    
    ReverseArrayIterator(T *ptr) : m_ptr(ptr) {}
    
    ReverseArrayIterator(const ReverseArrayIterator<T> &ReverseArrayIterator) {
        m_ptr = ReverseArrayIterator.m_ptr;
    }

    /**
     * @brief Advances ReverseArrayIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Retreats ReverseArrayIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Distance between two ReverseArrayIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(ReverseArrayIterator<T> const &rhs) const {
        return m_ptr - rhs.m_ptr;
    }

    ReverseArrayIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    ReverseArrayIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    T &operator*() const {
        return *m_ptr;
    }

    ReverseArrayIterator operator+(size_t n) const {
        return ReverseArrayIterator(m_ptr - n);
    }

    ReverseArrayIterator operator-(size_t n) const {
        return ReverseArrayIterator(m_ptr + n);
    }

    ptrdiff_t operator-(ReverseArrayIterator<T> const &rhs) const {
        return disctance(rhs);
    }

    ReverseArrayIterator &operator+=(size_t n) {
        return next(n);
    }

    ReverseArrayIterator &operator-=(size_t n) {
        return prev(n);
    }

    ReverseArrayIterator &operator++() {
        return next();
    }

    ReverseArrayIterator &operator--() {
        return prev();
    }

    ReverseArrayIterator operator++(int) {
        ReverseArrayIterator rai{m_ptr};
        next();
        return rai;
    }

    ReverseArrayIterator operator--(int) {
        ReverseArrayIterator rai{m_ptr};
        prev();
        return rai;
    }

    bool operator==(ReverseArrayIterator<T> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(ReverseArrayIterator<T> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(ReverseArrayIterator<T> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator<(ReverseArrayIterator<T> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator>=(ReverseArrayIterator<T> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }

    bool operator<=(ReverseArrayIterator<T> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }
};

template<typename T>
class ConstReverseArrayIterator {
    T const *m_ptr;

public:
    ConstReverseArrayIterator() = delete;
    
    ConstReverseArrayIterator(T const *ptr) : m_ptr(ptr) {}
    
    ConstReverseArrayIterator(const ConstReverseArrayIterator<T> &constReverseArrayIterator) {
        m_ptr = constReverseArrayIterator.m_ptr;
    }

    ConstReverseArrayIterator(const ReverseArrayIterator<T> &arrayIterator) {
        m_ptr = arrayIterator.m_ptr;
    }

    /**
     * @brief Advances ConstReverseArrayIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Retreats ConstReverseArrayIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Distance between two ConstReverseArrayIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(ConstReverseArrayIterator<T> const &rhs) const {
        return m_ptr - rhs.m_ptr;
    }

    ConstReverseArrayIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    ConstReverseArrayIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    T const &operator*() const {
        return *m_ptr;
    }

    ConstReverseArrayIterator operator+(size_t n) const {
        return ConstReverseArrayIterator(m_ptr - n);
    }

    ConstReverseArrayIterator operator-(size_t n) const {
        return ConstReverseArrayIterator(m_ptr + n);
    }

    ptrdiff_t operator-(ConstReverseArrayIterator<T> const &rhs) const {
        return disctance(rhs);
    }

    ConstReverseArrayIterator &operator+=(size_t n) {
        return next(n);
    }

    ConstReverseArrayIterator &operator-=(size_t n) {
        return prev(n);
    }

    ConstReverseArrayIterator &operator++() {
        return next();
    }

    ConstReverseArrayIterator &operator--() {
        return prev();
    }

    ConstReverseArrayIterator operator++(int) {
        ConstReverseArrayIterator crai{m_ptr};
        next();
        return crai;
    }

    ConstReverseArrayIterator operator--(int) {
        ConstReverseArrayIterator crai{m_ptr};
        prev();
        return crai;
    }

    bool operator==(ConstReverseArrayIterator<T> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(ConstReverseArrayIterator<T> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(ConstReverseArrayIterator<T> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator<(ConstReverseArrayIterator<T> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator>=(ConstReverseArrayIterator<T> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }

    bool operator<=(ConstReverseArrayIterator<T> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }
};

}