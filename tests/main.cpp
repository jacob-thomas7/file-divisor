#include "file_divisor.hpp"
#include <iostream>
#include <search.hpp>

int main(){
    try {
        file_divisor::SearchTerms terms;
        terms.add_system_path(std::filesystem::path("docs"));
        terms.add_filter(FILE_DIVISOR__FILTER__EXTENSION(".html"), file_divisor::FilterType::exclude);

        auto files = file_divisor::search(terms);
        
        for(auto file : files){
            std::cout << file << std::endl;
        }
    } catch(...){
        std::cout << "Some kind of exception";
    }
}