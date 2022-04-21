/**
 * @file Test.hpp
 * @author Soldatov Andrey (SoldatovAndreyWork@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>

//TODO: Change std::cout to  TAS::print or smth

#ifdef _WIN32
    #include <windows.h>
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #define SET_RED SetConsoleTextAttribute(hConsole, 12);
    #define SET_GREEN SetConsoleTextAttribute(hConsole, 10);
    #define SET_WHITE SetConsoleTextAttribute(hConsole, 15);
#elif __unix__
//TODO: Make unix vesion
#endif

unsigned long int test_count = 0; 
unsigned long int test_passed = 0; 
unsigned long int test_failed = 0; 

#define TEST_INIT(Name) \
test_count = 0; \
test_passed = 0; \
test_failed = 0; \
std::cout << "\nInitializing test suite \"" << #Name << "\"\n\n";

#define ANON_TEST_INIT \
test_count = 0; \
test_passed = 0; \
test_failed = 0; \
std::cout << "\nInitializing anonymous test suite\n\n";

#define ASSERT(boolean_value) \
    if(boolean_value) { \
        SET_GREEN \
        std::cout << "[V] Test_" << test_count << ": \"" << #boolean_value << "\" Passed!\n"; \
        test_passed++; \
    } \
    else { \
        SET_RED \
        std::cout << "[X] Test_" << test_count << ": \"" << #boolean_value << "\" Failed!\n"; \
        test_failed++; \
    } \
    SET_WHITE \
    test_count++;

#define ASSERT_EQ(val1, val2) \
    if(val1 == val2) { \
        SET_GREEN \
        std::cout << "[V] Test_" << test_count << ": \"" << #val1 << " == " << #val2 << "\" Passed!\n"; \
        test_passed++; \
    } \
    else { \
        SET_RED \
        std::cout << "[X] Test_" << test_count << ": \"" << #val1 << " == " << #val2 << "\" Failed!\n"; \
        test_failed++; \
    } \
    SET_WHITE \
    test_count++;

#define ASSERT_NOT_EQ(val1, val2) \
    if(val1 != val2) { \
        SET_GREEN \
        std::cout << "[V] Test_" << test_count << ": \"" << #val1 << " != " << #val2 << "\" Passed!\n"; \
        test_passed++; \
    } \
    else { \
        SET_RED \
        std::cout << "[X] Test_" << test_count << ": \"" << #val1 << " != " << #val2 << "\" Failed!\n"; \
        test_failed++; \
    } \
    SET_WHITE \
    test_count++;

#define TEST_END \
std::cout << "\nFrom " << test_count << " tests\n" << test_passed \
<< " Tests passed\n" << test_failed << " Tests failed\n";
