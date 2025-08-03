#include "search.hpp"

#include <iostream> //TODO remove

namespace file_divisor {
    Filter::Filter(std::function<bool(const std::filesystem::path&)> selector, FilterType type){
        this->selector = selector;
        this->type = type;
    }

    void Search::add_system_path(const std::filesystem::path& path){
        this->system_paths.emplace_back(path);
    }

    void Search::add_filter(const std::function<bool(const std::filesystem::path&)>& selector, FilterType type){
        this->filters.emplace_back(selector, type);
    }

    void Search::add_sort_function(const std::function<SortResult(const std::filesystem::path&, const std::filesystem::path&)>& function){
        this->sort_functions.emplace_back(function);
    }

    std::vector<std::filesystem::path>&& Search::search() const {
        std::vector<std::filesystem::path>* result = new std::vector<std::filesystem::path>();

        for(const std::filesystem::path& system_path : this->system_paths){
            this->add_valid_files(system_path, *result);
        }

        return move(*result);
    }

    void Search::add_valid_files(const std::filesystem::path& system_path, std::vector<std::filesystem::path>& result) const {
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
                
                // Sort during insertion
                {
                    int existing_path_index = 0;
                    while(existing_path_index < result.size() + 1){
                        SortResult compare_previous = compare(system_path, result, existing_path_index - 1);
                        SortResult compare_current = compare(system_path, result, existing_path_index);

                        if(
                            (compare_previous == SortResult::after && compare_current == SortResult::indeterminate) ||
                            (compare_previous == SortResult::after && compare_current == SortResult::before) ||
                            (compare_previous == SortResult::indeterminate && compare_current == SortResult::before)
                        ){
                            result.emplace(result.begin() + existing_path_index, system_path);
                            return;
                        }
                        existing_path_index++;
                    }
                    result.emplace_back(system_path);
                    break;
                }

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

    SortResult Search::compare(const std::filesystem::path& path, std::vector<std::filesystem::path>& result, int compare_to_index) const {
        if(compare_to_index < 0)
            return SortResult::after;
        
        if(compare_to_index >= result.size())
            return SortResult::before;
        
        std::filesystem::path& other_path = result[compare_to_index];

        std::cout << "There is already a " << other_path << " when pushing " << path << "\n";

        for(const auto& sort_function : this->sort_functions){
            SortResult sort_result = sort_function(path, other_path);
            if(sort_result != SortResult::indeterminate){
                return sort_result;
            }
        }

        return SortResult::indeterminate;
    }
}