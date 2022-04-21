#include <Test.hpp>

#include <Any.hpp>
#include <Array.hpp>
#include <String.hpp>
#include <Tuple.hpp>

//TODO: OMG... all... ALL the Tests for ALL lib

void Test() {

    // TAS::Any Tests
    TEST_INIT(TAS::Any)
    TAS::Any a = 10;
    ASSERT_EQ((int)a, 10);
    ASSERT_EQ(typeid((int)a), typeid(int))

    int b = (int)a;
    ASSERT_EQ(b, 10)
    ASSERT(a == 10)
    ASSERT(a != 11)

    TAS::Any str = TAS::String("Hello");
    ASSERT(str == TAS::String("Hello"))
    TEST_END
    // TAS::Any Tests

    // TAS::Array Tests
    TEST_INIT(TAS::Array)
    TAS::Array<int, 4> arr{2, 3, 4, 5};
    ASSERT_EQ(arr[0], 2)
    ASSERT_EQ(arr[1], 3)
    ASSERT_EQ(arr[2], 4)
    ASSERT_EQ(arr[3], 5)
    TEST_END
    // TAS::Array Tests
}

int main() {
    Test();
    return 0;
}