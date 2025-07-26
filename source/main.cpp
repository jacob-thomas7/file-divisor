#include <iostream>

#include "config.h"

using namespace file_divisor;

int main(){
    std::cout << config::PROJECT_NAME << " version " << config::PROJECT_VER << std::endl;
}