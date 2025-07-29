#include <iostream>

#include "config.hpp"
#include "file_divisor.hpp"

using namespace file_divisor;

int main(){
    std::cout << config::PROJECT_NAME << " version " << config::PROJECT_VER << std::endl;
    int test;
    std::cin >> test;
}