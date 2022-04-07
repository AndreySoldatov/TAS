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

namespace TAS
{

#define TEST_INIT \
unsigned long int test_count = 0; \
unsigned long int test_passed = 0; \
unsigned long int test_failed = 0; \

#ifdef TEST_INIT

#define ASSERT(boolean_value) \
    if(boolean_value) { \
        std::cout << "[V] Test_" << test_count << ": \"" << #boolean_value << "\" Passed!\n"; \
        test_passed++; \
    } \
    else { \
        std::cout << "[X] Test_" << test_count << ": \"" << #boolean_value << "\" Failed!\n"; \
        test_failed++; \
    } \
    test_count++; \

#define ASSERT_EQ(val1, val2) \
    if(val1 == val2) { \
        std::cout << "[V] Test_" << test_count << ": \"" << #val1 << " == " << #val2 << "\" Passed!\n"; \
        test_passed++; \
    } \
    else { \
        std::cout << "[X] Test_" << test_count << ": \"" << #val1 << " == " << #val2 << "\" Failed!\n"; \
        test_failed++; \
    } \
    test_count++; \

#define ASSERT_NOT_EQ(val1, val2) \
    if(val1 != val2) { \
        std::cout << "[V] Test_" << test_count << ": \"" << #val1 << " != " << #val2 << "\" Passed!\n"; \
        test_passed++; \
    } \
    else { \
        std::cout << "[X] Test_" << test_count << ": \"" << #val1 << " != " << #val2 << "\" Failed!\n"; \
        test_failed++; \
    } \
    test_count++; \

#define TEST_END \
    std::cout << "\nFrom " << test_count << " tests\n" << test_passed << " Tests passed\n" << test_failed << " Tests failed\n"; \

#endif

} // namespace TAS
