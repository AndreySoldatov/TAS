/**
 * @file String.hpp
 * @author Soldatov Andrey (SoldatovAndreyWork@gmail.com)
 * @brief This file contains the String class
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

//#define DEBUG

#ifdef DEBUG
#endif

#include <Print.hpp>

#include <stddef.h>
#include <iostream>

namespace TAS {

//FORWARDS
template<typename CharType>
size_t cStringLength(CharType const *);

template<typename PointerContainerType>
void memoryCopy(PointerContainerType *, PointerContainerType const *, size_t);

template<typename CharType>
class StringIterator;

template<typename CharType>
class ConstStringIterator;

template<typename CharType>
class ReverseStringIterator;

template<typename CharType>
class ConstReverseStringIterator;
//FORWARDS

/**
 * @brief This class represents basic generic character container
 * 
 * @tparam CharType type of the character
 * @tparam BlockSize size of the memory block that will be allocated when needed
 */
template<typename CharType, size_t BlockSize = 32>
class BasicString {
    size_t m_size{};
    size_t m_capacity{};
    CharType* m_data{nullptr};

public:
    /**
     * @brief represents infinite string index value
     * 
     */
    static const size_t nPos{SIZE_MAX};

    /**
     * @brief Construct an Empty String object
     * 
     */
    BasicString() {
        m_data = new CharType[BlockSize]{};
        m_capacity = BlockSize;
    }

    /**
     * @brief Construct a new Basic String object from C string
     * 
     * @param str 
     */
    BasicString(CharType const *str) {
        m_size = cStringLength(str);
        m_capacity = m_size + (BlockSize - m_size % BlockSize);
        m_data = new CharType[m_capacity]{};
        memoryCopy(m_data, str, m_size);
    }

    /**
     * @brief Construct a new Basic String object with size ```n``` and fills it with object ```chr```
     * 
     * @param chr 
     * @param n 
     */
    BasicString(CharType const &chr, size_t n) {
        m_size = n;
        m_capacity = m_size + (BlockSize - m_size % BlockSize);
        m_data = new CharType[m_capacity]{};
        fill(chr);
    }

    /**
     * @brief Construct a new Basic String object from one character. needed mostly for implicit conversions
     * 
     * @param chr 
     */
    BasicString(CharType const &chr) {
        m_size = 1;
        m_capacity = BlockSize;
        m_data = new CharType[m_capacity]{};
        fill(chr);
    }

    /**
     * @brief Construct a new Basic String object from another Basic String object
     * 
     * @param str 
     */
    BasicString(BasicString<CharType, BlockSize> const &str) : 
        m_size(str.m_size), 
        m_capacity(str.m_capacity),
        m_data(new CharType[str.m_capacity]{}) 
    {
        memoryCopy(m_data, str.m_data, m_size);
    }

    /**
     * @brief Construct a new Basic String object from std::string
     * 
     * @param str 
     */
    BasicString(std::basic_string<CharType> const &str)
    {
        m_size = str.length();
        m_capacity = m_size + (BlockSize - m_size % BlockSize);
        m_data = new CharType[m_capacity]{};
        memoryCopy(m_data, str.c_str(), m_size);
    }

    ~BasicString() {
        delete[] m_data;
    }

    BasicString &operator=(BasicString const &str) {
        delete[] m_data;
        m_size = str.m_size;
        m_capacity = str.m_capacity;
        m_data = new CharType[str.m_capacity]{};
        memoryCopy(m_data, str.m_data, m_size);
        return *this;
    }

    BasicString &operator=(CharType const &str) {
        delete[] m_data;
        m_size = cStringLength(str);
        m_capacity = m_size + (BlockSize - m_size % BlockSize);
        m_data = new CharType[m_capacity]{};
        memoryCopy(m_data, str, m_size);
        return *this;
    }

    /**
     * @brief Same as operator=()
     * 
     * @param str 
     * @return BasicString& 
     */
    BasicString &assign(BasicString const &str) {
        delete[] m_data;
        m_size = str.m_size;
        m_capacity = str.m_capacity;
        m_data = new CharType[str.m_capacity]{};
        memoryCopy(m_data, str.m_data, m_size);
        return *this;
    }

    /**
     * @brief Same as operator=()
     * 
     * @param str 
     * @return BasicString& 
     */
    BasicString &assign(CharType const &str) {
        delete[] m_data;
        m_size = cStringLength(str);
        m_capacity = m_size + (BlockSize - m_size % BlockSize);
        m_data = new CharType[m_capacity]{};
        memoryCopy(m_data, str, m_size);
        return *this;
    }

    /**
     * @brief if out of range throws std::out_of_range
     * 
     * @param index 
     */
    CharType &at(size_t index) {
        if(index >= m_size) throw std::out_of_range("Index is out of range");
        return m_data[index];
    }

    /**
     * @brief if out of range throws std::out_of_range
     * 
     * @param index 
     */
    const CharType &at(size_t index) const {
        if(index >= m_size) throw std::out_of_range("Index is out of range");
        return m_data[index];
    }

    /**
     * @brief WARNING: does not throw if exceedes
     * 
     * @param index 
     */
    CharType &operator[](size_t index) {
        return m_data[index];
    }

    /**
     * @brief WARNING: does not throw if exceedes
     * 
     * @param index 
     */
    const CharType &operator[](size_t index) const {
        return m_data[index];
    }

    /**
     * @brief raw char ptr
     * 
     * @return T* 
     */
    CharType *data() {
        return m_data;
    }

    /**
     * @brief returns pointer to constant cString
     * 
     * @return const CharType* 
     */
    const CharType *cString() const {
        return m_data;
    }

    /**
     * @brief constant First element
     * 
     * @return const CharType& 
     */
    const CharType &front() const {
        return m_data[0];
    }

    /**
     * @brief constant Last element
     * 
     * @return const CharType& 
     */
    const CharType &back() const {
        return m_data[m_size - 1];
    }

    /**
     * @brief variable first element
     * 
     * @return CharType& 
     */
    CharType &front() {
        return m_data[0];
    }

    /**
     * @brief variable last element
     * 
     * @return CharType& 
     */
    CharType &back() {
        return m_data[m_size - 1];
    }

    /**
     * @brief Iterator, pointing to the beginning of the string
     * 
     * @return StringIterator<CharType> 
     */
    StringIterator<CharType> begin() {
        return m_data;
    }

    /**
     * @brief constant Iterator, pointing to the beginning of the string
     * 
     * @return StringIterator<CharType> 
     */
    ConstStringIterator<CharType> cbegin() const {
        return m_data;
    }

    /**
     * @brief Reverse Iterator, pointing to the beginning(end) of the reversed string
     * 
     * @return StringIterator<CharType> 
     */
    ReverseStringIterator<CharType> rbegin() {
        return m_data + m_size - 1;
    }

    /**
     * @brief Constant Reverse Iterator, pointing to the beginning(end) of the reversed string
     * 
     * @return StringIterator<CharType> 
     */
    ConstReverseStringIterator<CharType> crbegin() const {
        return m_data + m_size - 1;
    }

    /**
     * @brief Iterator, pointing to the end of the string
     * 
     * @return StringIterator<CharType> 
     */
    StringIterator<CharType> end() {
        return m_data + m_size;
    }

    /**
     * @brief Constant Iterator, pointing to the end of the string
     * 
     * @return StringIterator<CharType> 
     */
    ConstStringIterator<CharType> cend() const {
        return m_data + m_size;
    }

    /**
     * @brief Reverse Iterator, pointing to the end(beginning) of the reversed string
     * 
     * @return StringIterator<CharType> 
     */
    ReverseStringIterator<CharType> rend() {
        return m_data - 1;
    }

    /**
     * @brief Constant Reverse Iterator, pointing to the end(beginning) of the reversed string
     * 
     * @return StringIterator<CharType> 
     */
    ConstReverseStringIterator<CharType> crend() const {
        return m_data - 1;
    }

    bool empty() const {
        return !m_size;
    }

    size_t size() const {
        return m_size;
    }
    
    /**
     * @brief same as size, but preferred for using in templated functions
     * 
     * @return size_t 
     */
    size_t length() const {
        return m_size;
    }

    /**
     * @brief returns the amount of characters that are allocated right now
     * 
     * @return size_t 
     */
    size_t capacity() const {
        return m_capacity;
    }

    /**
     * @brief allocates new characters if needed
     * 
     * @param capacity 
     * @return BasicString& 
     */
    BasicString &reserve(size_t capacity) {
        if(capacity > m_capacity) {
            m_capacity = capacity;
            CharType *tmp = new CharType[capacity]{};
            memoryCopy(tmp, m_data, m_size);
            delete[] m_data;
            m_data = tmp;
        }
        return *this;
    }

    /**
     * @brief deallocates unused space
     * 
     * @return BasicString& 
     */
    BasicString &shrinkToFit() {
        m_capacity = m_size;
        CharType *tmpStr = new CharType[m_size];
        memoryCopy(tmpStr, m_data, m_size);
        delete[] m_data;
        m_data = tmpStr;
        return *this;
    }

    /**
     * @brief "Hello" -> ""
     * 
     * @return BasicString& 
     */
    BasicString &clear() {
        if(m_size > 0) {
            m_size = 0;
            delete[] m_data;
            m_data = new CharType[BlockSize]{};
            m_capacity = BlockSize;
        }
        return *this;
    }

    /**
     * @brief fills string with char
     * 
     * @param ch 
     * @return BasicString& 
     */
    BasicString &fill(CharType const &ch) {
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = ch;
        }
        return *this;
    }

    /**
     * @brief inserts char at index
     * 
     * @param ch 
     * @param index 
     * @return BasicString& 
     */
    BasicString &insert(CharType const &ch, size_t index) {
        assign(span(0, index).append(ch).append(span(index)));
        return *this;
    }

    /**
     * @brief inserts String at index
     * 
     * @param str 
     * @param index 
     * @return BasicString& 
     */
    BasicString &insert(BasicString const &str, size_t index) {
        assign(span(0, index).append(str).append(span(index)));
        return *this;
    }

    /**
     * @brief erases a span-defined(first-last) portion of string
     * WARNING: FIRST MUST BE <= THAN LAST
     * 
     * @param first 
     * @param last 
     * @return BasicString& 
     */
    BasicString &eraseSpan(size_t first, size_t last = BasicString::nPos) {
        assign(span(0, first) + span(last));
        return *this;  
    }

    /**
     * @brief erases a subString-defined(first-length) portion of string
     * 
     * @param first 
     * @param n 
     * @return BasicString& 
     */
    BasicString &eraseSubString(size_t first, size_t n = 1) {
        assign(span(0, first) + span(first + n));
        return *this;
    }

    /**
     * @brief appends value to the end of the string
     * 
     * @param chr 
     * @return BasicString& 
     */
    BasicString &append(CharType const &chr) {
        if(m_size == m_capacity) {
            reserve(m_size + BlockSize);
        }
        
        m_data[m_size++] = chr;
        return *this;
    }

    /**
     * @brief appends value to the end of the string
     * 
     * @param chr 
     * @return BasicString& 
     */
    BasicString &append(BasicString const &str) {
        if(m_size + str.size() > m_capacity) {
            reserve(str.size() + (BlockSize - str.size() % BlockSize));
        }

        for (size_t i = 0; i < str.size(); i++) {
            m_data[i + m_size] = str[i];
        }

        m_size += str.size();
        return *this;
    }

    /**
     * @brief appends value to the end of the string
     * 
     * @param chr 
     * @return BasicString& 
     */
    BasicString &pushBack(CharType const &c) {
        return append(c);
    }

    /**
     * @brief appends value to the end of the string
     * 
     * @param chr 
     * @return BasicString& 
     */
    BasicString &pushBack(BasicString const &str) {
        return append(str);
    }

    /**
     * @brief deletes last character
     * 
     * @param chr 
     * @return BasicString& 
     */
    BasicString &popBack() {
        return eraseSubString(m_size - 1);
    }

    BasicString operator+(CharType const &chr) const {
        BasicString res{*this};
        return res.append(chr);
    }

    BasicString operator+(BasicString const &str) const {
        BasicString res{*this};
        return res.append(str);
    }

    BasicString operator+=(BasicString const &str) {
        return append(str);
    }

    /**
     * @brief returns portion of the String defined by first and last indecies
     * INFO: first can even be larger than last, try it some time)
     * 
     * @param first 
     * @param last 
     * @return BasicString 
     */
    BasicString span(size_t first, size_t last = BasicString::nPos) const {
        if(last < first) {
            BasicString res;
            for (ConstReverseStringIterator<CharType> i = cbegin() + (first <= m_size ? first : m_size) - 1; i <= cbegin() + last; i++)
            {
                res.append(*i);
            }
            return res;
        }
        else if(last == first) {
            return {};
        }
        else {
            BasicString res;
            for (ConstStringIterator<CharType> i = cbegin() + first; i < (last >= m_size ? cend() : cbegin() + last); i++)
            {
                res.append(*i);
            }
            return res;
        }
    }

    /**
     * @brief returns portion of the String defined by first and length
     * INFO: length can even be negative, try it some time)
     * 
     * @param first 
     * @param last 
     * @return BasicString 
     */
    BasicString subString(size_t first, int n = 1) const {
        return span(first, first + n);
    }

    bool startsWith(BasicString const &str) const {
        for (size_t i = 0; i < str.size(); i++)
        {
            if(m_data[i] != str[i]) return false;    
        }
        return true;
    }

    bool endsWith(BasicString const &str) const {
        for (size_t i = 0; i < str.size(); i++)
        {
            if(m_data[(m_size - str.size()) + i] != str[i]) return false;    
        }
        return true;
    }

    bool contains(BasicString const &str) const {
        for (size_t i = 0; i < m_size - str.size() + 1; i++)
        {
            bool res = true;
            for (size_t j = 0; j < str.size(); j++)
            {
                if(m_data[i + j] != str[j]) res = false;
            }
            if(res) return true;
        }
        return false;
    }

    bool operator==(BasicString const &rhs) const {
        return (m_size == rhs.size()) && contains(rhs);
    }

    bool operator!=(BasicString const &rhs) const {
        return !(*this == rhs);
    }

    bool equals(BasicString const &rhs) const {
        return (m_size == rhs.size()) && contains(rhs);
    }

    /**
     * @brief replaces span definded portion of string with substr
     * WARNING: FIRST MUST BE <= THAN LAST
     * 
     * @param str 
     * @param first 
     * @param last 
     * @return BasicString& 
     */
    BasicString &replaceSpan(BasicString const &str, size_t first, size_t last = BasicString::nPos) {
        assign(span(0, first) + str + span(last));
        return *this;
    }

    /**
     * @brief replaces subString definded portion of string with substr
     * 
     * @param str 
     * @param first 
     * @param last 
     * @return BasicString& 
     */
    BasicString &replaceSubString(BasicString const &str, size_t first, size_t n = 1) {
        assign(span(0, first) + str + span(first + n));
        return *this;
    }

    //TODO: Maybe implement smth like std::copy();

    /**
     * @brief WARNING: if I were you, I would not use this yet
     * 
     * @param newSize 
     * @return BasicString&
     */
    BasicString &resize(size_t newSize, CharType const &fill = {}) {
        if(newSize > m_size) {
            reserve(newSize + (BlockSize - newSize % BlockSize));
            for (size_t i = m_size; i < newSize; i++)
            {
                m_data[i] = fill;
            }
        } else {
            for (size_t i = newSize; i < m_size; i++)
            {
                m_data[i] = {};
            }
        }
        m_size = newSize;
        return *this;
    }

    /**
     * @brief Swaps content of two strings
     * 
     * @param other 
     * @return BasicString& 
     */
    BasicString &swap(BasicString &other) {
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_data, other.m_data);
        return *this;
    }

    /**
     * @brief returns index of first occurence of substr
     * if not found returns String::nPos
     * 
     * @param str 
     * @return size_t 
     */
    size_t findFirst(BasicString const &str) const {
        for (size_t i = 0; i < m_size - str.size() + 1; i++)
        {
            bool res = true;
            for (size_t j = 0; j < str.size(); j++)
            {
                if(m_data[i + j] != str[j]) res = false;
            }
            if(res) return i;
        }
        return BasicString::nPos;
    }

    /**
     * @brief returns index of last occurence of substr
     * if not found returns String::nPos
     * 
     * @param str 
     * @return size_t 
     */
    size_t findLast(BasicString const &str) const {
        for (size_t i = m_size - str.size(); i >= 0 ; i--)
        {
            bool res = true;
            for (size_t j = 0; j < str.size(); j++)
            {
                if(m_data[i + j] != str[j]) res = false;
            }
            if(res) return i;
        }
        return BasicString::nPos;
    }

    /**
     * @brief returns index of first occurence of ANY CHARACTER OF SUBSTR
     * if not found returns String::nPos
     * 
     * @param str 
     * @return size_t 
     */
    size_t findFirstOf(BasicString const &str) const {
        for (size_t i = 0; i < m_size; i++)
        {
            for (size_t j = 0; j < str.size(); j++)
            {
                if(m_data[i] == str[j]) return i;
            }
        }
        return BasicString::nPos;
    }

    /**
     * @brief returns index of last occurence of ANY CHARACTER OF SUBSTR
     * if not found returns String::nPos
     * 
     * @param str 
     * @return size_t 
     */
    size_t findLastOf(BasicString const &str) const {
        for (size_t i = m_size - 1; i >= 0; i--)
        {
            for (size_t j = 0; j < str.size(); j++)
            {
                if(m_data[i] == str[j]) return i;
            }
        }
        return BasicString::nPos;
    }
};

template<typename CharType>
class StringIterator {
    friend ReverseStringIterator<CharType>;

    CharType *m_ptr;

public:
    StringIterator() = delete;
    
    StringIterator(CharType *ptr) : m_ptr(ptr) {}
    
    StringIterator(const StringIterator<CharType> &StringIterator) {
        m_ptr = StringIterator.m_ptr;
    }

    StringIterator(const ReverseStringIterator<CharType> &StringIterator) {
        m_ptr = StringIterator.m_ptr;
    }

    /**
     * @brief Advances StringIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Retreats StringIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Distance between two StringIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(StringIterator<CharType> const &rhs) const {
        return rhs.m_ptr - m_ptr;
    }

    StringIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    StringIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    CharType &operator*() const {
        return *m_ptr;
    }

    StringIterator operator+(size_t n) const {
        return StringIterator(m_ptr + n);
    }

    StringIterator operator-(size_t n) const {
        return StringIterator(m_ptr - n);
    }

    ptrdiff_t operator-(StringIterator<CharType> const &rhs) const {
        return disctance(rhs);
    }

    StringIterator &operator+=(size_t n) {
        return next(n);
    }

    StringIterator &operator-=(size_t n) {
        return prev(n);
    }

    StringIterator &operator++() {
        return next();
    }

    StringIterator &operator--() {
        return prev();
    }

    StringIterator operator++(int) {
        StringIterator ai{m_ptr};
        next();
        return ai;
    }

    StringIterator operator--(int) {
        StringIterator ai{m_ptr};
        prev();
        return ai;
    }

    bool operator==(StringIterator<CharType> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(StringIterator<CharType> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(StringIterator<CharType> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator<(StringIterator<CharType> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator>=(StringIterator<CharType> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }

    bool operator<=(StringIterator<CharType> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }
};

template<typename CharType>
class ConstStringIterator {
    friend StringIterator<CharType>;
    friend ReverseStringIterator<CharType>;
    friend ConstReverseStringIterator<CharType>;

    CharType const *m_ptr;

public:
    ConstStringIterator() = delete;
    
    ConstStringIterator(CharType const *ptr) : m_ptr(ptr) {}
    
    ConstStringIterator(const ConstStringIterator<CharType> &constStringIterator) {
        m_ptr = constStringIterator.m_ptr;
    }

    ConstStringIterator(const StringIterator<CharType> &stringIterator) {
        m_ptr = stringIterator.m_ptr;
    }

    ConstStringIterator(const ReverseStringIterator<CharType> &StringIterator) {
        m_ptr = StringIterator.m_ptr;
    }

    ConstStringIterator(const ConstReverseStringIterator<CharType> &StringIterator) {
        m_ptr = StringIterator.m_ptr;
    }

    /**
     * @brief Advances ConstStringIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Retreats ConstStringIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Distance between two ConstStringIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(ConstStringIterator<CharType> const &rhs) const {
        return rhs.m_ptr - m_ptr;
    }

    ConstStringIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    ConstStringIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    CharType const &operator*() const {
        return *m_ptr;
    }

    ConstStringIterator operator+(size_t n) const {
        return ConstStringIterator(m_ptr + n);
    }

    ConstStringIterator operator-(size_t n) const {
        return ConstStringIterator(m_ptr - n);
    }

    ptrdiff_t operator-(ConstStringIterator<CharType> const &rhs) const {
        return disctance(rhs);
    }

    ConstStringIterator &operator+=(size_t n) {
        return next(n);
    }

    ConstStringIterator &operator-=(size_t n) {
        return prev(n);
    }

    ConstStringIterator &operator++() {
        return next();
    }

    ConstStringIterator &operator--() {
        return prev();
    }

    ConstStringIterator operator++(int) {
        ConstStringIterator cai{m_ptr};
        next();
        return cai;
    }

    ConstStringIterator operator--(int) {
        ConstStringIterator cai{m_ptr};
        prev();
        return cai;
    }

    bool operator==(ConstStringIterator<CharType> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(ConstStringIterator<CharType> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(ConstStringIterator<CharType> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator<(ConstStringIterator<CharType> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator>=(ConstStringIterator<CharType> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }

    bool operator<=(ConstStringIterator<CharType> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }
};





template<typename CharType>
class ReverseStringIterator {
    friend StringIterator<CharType>;

    CharType *m_ptr;

public:
    ReverseStringIterator() = delete;
    
    ReverseStringIterator(CharType *ptr) : m_ptr(ptr) {}
    
    ReverseStringIterator(const ReverseStringIterator<CharType> &ReverseStringIterator) {
        m_ptr = ReverseStringIterator.m_ptr;
    }

    ReverseStringIterator(const StringIterator<CharType> &stringIterator) {
        m_ptr = stringIterator.m_ptr;
    }

    /**
     * @brief Advances ReverseStringIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Retreats ReverseStringIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Distance between two ReverseStringIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(ReverseStringIterator<CharType> const &rhs) const {
        return m_ptr - rhs.m_ptr;
    }

    ReverseStringIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    ReverseStringIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    CharType &operator*() const {
        return *m_ptr;
    }

    ReverseStringIterator operator+(size_t n) const {
        return ReverseStringIterator(m_ptr - n);
    }

    ReverseStringIterator operator-(size_t n) const {
        return ReverseStringIterator(m_ptr + n);
    }

    ptrdiff_t operator-(ReverseStringIterator<CharType> const &rhs) const {
        return disctance(rhs);
    }

    ReverseStringIterator &operator+=(size_t n) {
        return next(n);
    }

    ReverseStringIterator &operator-=(size_t n) {
        return prev(n);
    }

    ReverseStringIterator &operator++() {
        return next();
    }

    ReverseStringIterator &operator--() {
        return prev();
    }

    ReverseStringIterator operator++(int) {
        ReverseStringIterator rai{m_ptr};
        next();
        return rai;
    }

    ReverseStringIterator operator--(int) {
        ReverseStringIterator rai{m_ptr};
        prev();
        return rai;
    }

    bool operator==(ReverseStringIterator<CharType> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(ReverseStringIterator<CharType> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(ReverseStringIterator<CharType> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator<(ReverseStringIterator<CharType> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator>=(ReverseStringIterator<CharType> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }

    bool operator<=(ReverseStringIterator<CharType> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }
};

template<typename CharType>
class ConstReverseStringIterator {
    friend StringIterator<CharType>;
    friend ConstStringIterator<CharType>;
    friend ReverseStringIterator<CharType>;

    CharType const *m_ptr;

public:
    ConstReverseStringIterator() = delete;
    
    ConstReverseStringIterator(CharType const *ptr) : m_ptr(ptr) {}
    
    ConstReverseStringIterator(const ConstReverseStringIterator<CharType> &constReverseStringIterator) {
        m_ptr = constReverseStringIterator.m_ptr;
    }

    ConstReverseStringIterator(const ReverseStringIterator<CharType> &stringIterator) {
        m_ptr = stringIterator.m_ptr;
    }

    ConstReverseStringIterator(const ConstStringIterator<CharType> &constStringIterator) {
        m_ptr = constStringIterator.m_ptr;
    }

    ConstReverseStringIterator(const StringIterator<CharType> &stringIterator) {
        m_ptr = stringIterator.m_ptr;
    }

    /**
     * @brief Advances ConstReverseStringIterator on n positions
     * 
     * @param n 
     */
    void advance(size_t n = 1) {
        m_ptr -= n;
    }

    /**
     * @brief Retreats ConstReverseStringIterator on n positions
     * 
     * @param n 
     */
    void retreat(size_t n = 1) {
        m_ptr += n;
    }

    /**
     * @brief Distance between two ConstReverseStringIterator
     * 
     * @param rhs 
     * @return ptrdiff_t 
     */
    ptrdiff_t disctance(ConstReverseStringIterator<CharType> const &rhs) const {
        return m_ptr - rhs.m_ptr;
    }

    ConstReverseStringIterator &next(size_t n = 1) {
        advance(n);
        return *this;
    }

    ConstReverseStringIterator &prev(size_t n = 1) {
        retreat(n);
        return *this;
    }

    CharType const &operator*() const {
        return *m_ptr;
    }

    ConstReverseStringIterator operator+(size_t n) const {
        return ConstReverseStringIterator(m_ptr - n);
    }

    ConstReverseStringIterator operator-(size_t n) const {
        return ConstReverseStringIterator(m_ptr + n);
    }

    ptrdiff_t operator-(ConstReverseStringIterator<CharType> const &rhs) const {
        return disctance(rhs);
    }

    ConstReverseStringIterator &operator+=(size_t n) {
        return next(n);
    }

    ConstReverseStringIterator &operator-=(size_t n) {
        return prev(n);
    }

    ConstReverseStringIterator &operator++() {
        return next();
    }

    ConstReverseStringIterator &operator--() {
        return prev();
    }

    ConstReverseStringIterator operator++(int) {
        ConstReverseStringIterator crai{m_ptr};
        next();
        return crai;
    }

    ConstReverseStringIterator operator--(int) {
        ConstReverseStringIterator crai{m_ptr};
        prev();
        return crai;
    }

    bool operator==(ConstReverseStringIterator<CharType> const &rhs) const {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(ConstReverseStringIterator<CharType> const &rhs) const {
        return m_ptr != rhs.m_ptr;
    }

    bool operator>(ConstReverseStringIterator<CharType> const &rhs) const {
        return m_ptr < rhs.m_ptr;
    }

    bool operator<(ConstReverseStringIterator<CharType> const &rhs) const {
        return m_ptr > rhs.m_ptr;
    }

    bool operator>=(ConstReverseStringIterator<CharType> const &rhs) const {
        return m_ptr <= rhs.m_ptr;
    }

    bool operator<=(ConstReverseStringIterator<CharType> const &rhs) const {
        return m_ptr >= rhs.m_ptr;
    }
};

//TYPEDEFS
/**
 * @brief most common string type.
 * Typedef of TAS::BasicString<char, 32>
 * 
 */
typedef BasicString<char, 32> String;
//TYPEDEFS

template<typename CharType>
size_t cStringLength(CharType const *str) {
    size_t count{};
    while(str[count]) {
        count++;
    };
    return count;
}

template<typename PointerContainerType>
void memoryCopy(PointerContainerType *destination, PointerContainerType const *source, size_t n) {
    for (size_t i = 0; i < n; i++)
    {
        destination[i] = source[i];
    }
}

template<typename CharType, size_t BlockSize>
void print(BasicString<CharType, BlockSize> const &str) {
    std::cout << str.cString();
}

template<typename CharType, size_t BlockSize>
std::istream &operator>>(std::istream &is, BasicString<CharType, BlockSize> &str) {
    //FIXME:
    return is >> str.data();
}

}