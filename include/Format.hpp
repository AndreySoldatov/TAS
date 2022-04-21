/**
 * @file Format.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <Print.hpp>
#include <String.hpp>

namespace TAS
{

//TODO: Change std::cout to TAS::print();
template<typename T>
void recursiveFormatPrint(String const &str, T const &val) {
    if(str.findFirst("{}") == String::nPos) throw std::runtime_error("Bad String");

    print(str.span(0, str.findFirst("{}")));
    print(val);
    print(str.span(str.findFirst("{}") + 2));
}

template<typename T, typename ...Args>
void recursiveFormatPrint(String const &str, T const &val, const Args &... args) {
    if(str.findFirst("{}") == String::nPos) throw std::runtime_error("Bad String");

    print(str.span(0, str.findFirst("{}")));
    print(val);

    recursiveFormatPrint(str.span(str.findFirst("{}") + 2), args...);
}

template<typename ...Args>
void formatPrint(String const &str, const Args&... args) {
    recursiveFormatPrint(str, args...);
}

} // namespace TAS
