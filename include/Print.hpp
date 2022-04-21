/**
 * @file Print.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>

namespace TAS
{

template<typename T>
void print(T const &val) {
    std::cout << val;
}

} // namespace TAS
