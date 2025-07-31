#pragma once

#include <filesystem>
#include <functional>
#include <stdexcept>
#include <vector>

//! @defgroup filter_macros Filter Presets
//! A set of commonly used filter selectors.

//! Generates a Filter selector function which selects files with the given extension.
//! @ingroup filter_macros
#define FILE_DIVISOR__FILTER__EXTENSION(ext) [](const std::filesystem::path& path){ return path.extension() == (ext); }

namespace file_divisor {
    
    //! Determines how a filter is used to include or exclude files.
    enum class FilterType {
        exclude, //!< Excludes files that a Filter evaluator function returns true on.
        include  //!< Includes files that a Filter evaluator function returns true on.
    };

    //! Determines what files should be included in a search.
    struct Filter {
        std::function<bool(const std::filesystem::path&)> selector; //!< A function to specify which files to select. Selects by returning true.
        FilterType type; //!< Determines if selected files should be included or excluded.

        //! Constructor for all members.
        Filter(std::function<bool(const std::filesystem::path&)> selector, FilterType type){
            this->selector = selector;
            this->type = type;
        }
    };

    //! Stores information on what files to search for.
    class SearchTerms {
        public:
        
        //! Stores the top-level system directories to begin searching.
        //! Supports files of type std::filesystem::file_type::regular and std::filesystem::file_type::directory.
        std::vector<std::filesystem::path> system_paths;

        //! Allows multiple Filters to be applied for clarity.
        std::vector<Filter> filters;

        //! Adds a system path to search for files.
        void add_system_path(const std::filesystem::path& path);

        //! Adds a function to filter files.
        void add_filter(const std::function<bool(const std::filesystem::path&)>& selector, FilterType type);

        //sort
    };

    //! Finds all files that match the given search terms.
    //! Searches in all given system paths, excludes filter matches, and sorts based on the given sorting function.
    //!
    //! @param search_terms The SearchTerms to evaluate.
    //! @return A vector of system paths which match the SearchTerms.
    std::vector<std::filesystem::path>&& search(const SearchTerms& search_terms);
}