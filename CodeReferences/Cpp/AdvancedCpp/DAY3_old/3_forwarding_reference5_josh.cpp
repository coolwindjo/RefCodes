#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1 = {1,1,1,1,1};

    for (auto& n: v1){
        n = 0;
    }

    std::vector<bool> v2 = {1,1,1,1,1};

    // for (auto& n : v2){ // Error!
    for (auto&& n : v2){ // OK
        n = 0;
    }
    return 0;
}