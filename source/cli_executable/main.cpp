#include <iostream>

#include "config.h"
#include "file_divisor.hpp"

using namespace file_divisor;

int main(){
    std::cout << add(5, 5) << std::endl;
    std::cout << config::PROJECT_NAME << " version " << config::PROJECT_VER << std::endl;
    int test;
    std::cin >> test;
}