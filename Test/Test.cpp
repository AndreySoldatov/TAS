#include <Test.hpp>

#include <Any.hpp>
#include <Array.hpp>
#include <String.hpp>
#include <Tuple.hpp>

void Test() {
    using namespace TAS;

    TEST_INIT

    /// TAS::ANY TESTS
    Any a = 10;
    ASSERT_EQ((int)a, 10);
    ASSERT_EQ(typeid((int)a), typeid(int))

    int b = (int)a;
    ASSERT_EQ(b, 10)
    ASSERT(a == 10)
    ASSERT(a != 11)

    Any str = String("Hello");
    ASSERT(str == String("Hello"))
    /// TAS::ANY TESTS

    TEST_END
}

int main() {
    Test();
    return 0;
}