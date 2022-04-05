# TAS
TAS is a C++ standard library implementation that aims to deliver **easier**, more **straightforward**, but yet as **powerful** user experience of working with standard library:

```cpp
#include <Array.hpp>
#include <String.hpp>

using namespace TAS;

int main() {
    Array<String, 4> arr{"Hello", "World", "and", "Github"};

    arr.forEach([](String const &str) {
        std::cout << str << "\n";
    });
    
    return 0;
}
```
