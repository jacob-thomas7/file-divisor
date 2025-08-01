#include "search.hpp"

#include <iostream>

namespace file_divisor {
    void Search::add_system_path(const std::filesystem::path& path){
        this->system_paths.emplace_back(path);
    }

    void Search::add_filter(const std::function<bool(const std::filesystem::path&)>& selector, FilterType type){
        this->filters.emplace_back(selector, type);
    }

    std::vector<std::filesystem::path>&& Search::search(){
        std::vector<std::filesystem::path>* result = new std::vector<std::filesystem::path>();

        for(const std::filesystem::path& system_path : this->system_paths){
            this->add_valid_files(system_path, *result);
        }

        return move(*result);
    }

    void Search::add_valid_files(const std::filesystem::path& system_path, std::vector<std::filesystem::path>& result){
        auto file_status = std::filesystem::status(system_path);
        
        switch(file_status.type()){
            case std::filesystem::file_type::regular:
                // Filter results
                for(const file_divisor::Filter& filter : this->filters){
                    bool filter_result = filter.selector(system_path);
                    if(
                        (filter_result && filter.type == file_divisor::FilterType::exclude) ||
                        (!filter_result && filter.type == file_divisor::FilterType::include)
                    ){
                        return;
                    }
                }

                result.emplace_back(system_path);
                break;

            case std::filesystem::file_type::directory:
                // Recursive directory search
                for(const std::filesystem::directory_entry& directory_entry : std::filesystem::directory_iterator(system_path)){
                    add_valid_files(directory_entry.path(), result);
                }
                break;

            default:
                throw std::invalid_argument("file_divisor::search does not support searching from this file type: " + system_path.generic_string());
        }
    }
}