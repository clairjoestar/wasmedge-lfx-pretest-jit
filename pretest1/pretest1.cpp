#include <iostream>
#include <initializer_list>

int main() {
    int result = 0;
    for (int x : {4, 2, 8, 5}) {
        if (x >= 4) {
            result += x * x;
        } else {
            result -= x;
        }
        std::cout << "x = " << x << ", result = " << result << std::endl;
    }
    
    std::cout << "Final result: " << result << std::endl;
    
    return 0;
}