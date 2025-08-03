#include "file_divisor.hpp"
#include <iostream>

int main(){
    try {
        file_divisor::Search search;
        search.add_system_path(std::filesystem::path("tests/files"));
        search.add_filter(FILE_DIVISOR__FILTER__EXTENSION(".html"), file_divisor::FilterType::exclude);

        search.add_sort_function(file_divisor::sort_stem);
        search.add_sort_function(file_divisor::sort_extension_reverse);
        
        auto files = search.search();
        
        for(auto file : files){
            std::cout << file << std::endl;
        }
    } catch(...){
        std::cout << "Some kind of exception";
    }
}