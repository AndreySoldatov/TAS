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

//#define DEBUG

#ifdef DEBUG
#endif

#include <stddef.h>
#include <iostream>

namespace TAS {

//FORWARDS
template<typename CharType>
size_t cStringLength(CharType const *);

template<typename PointerContainerType>
void memoryCopy(PointerContainerType *, PointerContainerType const *, size_t);
//FORWARDS

template<typename CharType, size_t BlockSize = 32>
class BasicString {
    size_t m_size{};
    size_t m_capacity{};
    CharType* m_data{nullptr};

public:
    static const size_t nPos{SIZE_MAX};

    BasicString() {
        m_data = new CharType[BlockSize]{};
        m_capacity = BlockSize;
    }

    BasicString(CharType const *str) {
        m_size = cStringLength(str);
        m_capacity = m_size + (BlockSize - m_size % BlockSize);
        m_data = new CharType[m_capacity]{};
        memoryCopy(m_data, str, m_size);
    }

    BasicString(CharType const &chr, size_t n) {
        m_size = n;
        m_capacity = m_size + (BlockSize - m_size % BlockSize);
        m_data = new CharType[m_capacity]{};
        fill(chr);
    }

    BasicString(CharType const &chr) {
        m_size = 1;
        m_capacity = BlockSize;
        m_data = new CharType[m_capacity]{};
        fill(chr);
    }

    BasicString(BasicString<CharType, BlockSize> const &str) : 
        m_size(str.m_size), 
        m_capacity(str.m_capacity),
        m_data(new CharType[str.m_capacity]{}) 
    {
        memoryCopy(m_data, str.m_data, m_size);
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

    BasicString &assign(BasicString const &str) {
        delete[] m_data;
        m_size = str.m_size;
        m_capacity = str.m_capacity;
        m_data = new CharType[str.m_capacity]{};
        memoryCopy(m_data, str.m_data, m_size);
        return *this;
    }

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

    const CharType *cString() const {
        return m_data;
    }

    const CharType &front() const {
        return m_data[0];
    }

    const CharType &back() const {
        return m_data[m_size - 1];
    }

    CharType &front() {
        return m_data[0];
    }

    CharType &back() {
        return m_data[m_size - 1];
    }

    //TODO:
    /**
     * Iterators:
     *      begin
     *      cbegin
     *      
     *      (C++11)
     *      
     *      returns an iterator to the beginning
     *      (public member function)
     *      end
     *      cend
     *      
     *      (C++11)
     *      
     *      returns an iterator to the end
     *      (public member function)
     *      rbegin
     *      crbegin
     *      
     *      (C++11)
     *      
     *      returns a reverse iterator to the beginning
     *      (public member function)
     *      rend
     *      crend
     *      
     *      (C++11)
     *      
     *      returns a reverse iterator to the end
     *      (public member function)
     */

    bool empty() const {
        return !m_size;
    }

    size_t size() const {
        return m_size;
    }

    size_t length() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

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

    //TODO: Maybe implement smth like shrink_to_fit

    BasicString &clear() {
        if(m_size > 0) {
            m_size = 0;
            delete[] m_data;
            m_data = new CharType[BlockSize]{};
            m_capacity = BlockSize;
        }
        return *this;
    }

    BasicString &fill(CharType const &ch) {
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = ch;
        }
        return *this;
    }

    //TODO: implement with TAS::StringIterator
    BasicString &insert(CharType const &ch, size_t index) {
        assign(span(0, index).append(ch).append(span(index)));
        return *this;
    }

    //TODO: implement with TAS::StringIterator
    BasicString &insert(BasicString const &str, size_t index) {
        assign(span(0, index).append(str).append(span(index)));
        return *this;
    }

    //TODO: implement with TAS::StringIterator
    BasicString &eraseSpan(size_t first, size_t last = BasicString::nPos) {
        assign(span(0, first) + span(last));
        return *this;  
    }

    //TODO: implement with TAS::StringIterator
    BasicString &eraseSubString(size_t first, size_t n = 1) {
        assign(span(0, first) + span(first + n));
        return *this;
    }

    BasicString &append(CharType const &chr) {
        if(m_size == m_capacity) {
            reserve(m_size + BlockSize);
        }
        
        m_data[m_size++] = chr;
        return *this;
    }

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

    BasicString &pushBack(CharType const &c) {
        append(c);
        return *this;
    }

    BasicString &popBack() {
        eraseSubString(m_size - 1);
        return *this;
    }

    BasicString operator+(CharType const &chr) {
        BasicString res{*this};
        return res.append(chr);
    }

    BasicString operator+(BasicString const &str) {
        BasicString res{*this};
        return res.append(str);
    }

    //TODO: implement with TAS::StringIterator
    BasicString span(size_t first, size_t last = BasicString::nPos) {
        if(last < first) throw std::runtime_error("Ay ay, last < first");
        else if(last == first) {
            return {};
        }
        else {
            BasicString res;
            for (size_t i = first; i < (last >= m_size ? m_size : last); i++)
            {
                res.append(m_data[i]);
            }
            return res;
        }
    }

    //TODO: implement with TAS::StringIterator
    BasicString subString(size_t first, size_t n = 1) {
        return span(first, first + n);
    }
};

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
std::ostream &operator<<(std::ostream &os, BasicString<CharType, BlockSize> const &str) {
    return os << str.cString();
}

}