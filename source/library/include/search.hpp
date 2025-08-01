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
        exclude, //!< Excludes files that a Filter selector function returns true on. Includes files that it returns false on.
        include  //!< Includes files that a Filter selector function returns true on. Excludes files that it returns false on.
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
    class Search {
        public:
        
        //! Stores the top-level system directories to begin searching.
        //! Supports files of type std::filesystem::file_type::regular and std::filesystem::file_type::directory.
        std::vector<std::filesystem::path> system_paths;

        //! Allows multiple Filters to be applied for clarity.
        std::vector<Filter> filters;

        //! Adds a system path to search for files.
        void add_system_path(const std::filesystem::path& path);

        //! Adds a filter to apply when searching for files.
        void add_filter(const std::function<bool(const std::filesystem::path&)>& selector, FilterType type);

        //TODO: sort

        //! Finds all files that match the given search terms.
        //! Searches in all given system paths, excludes filter matches, and sorts based on the given sorting function.
        //!
        //! @throws std::invalid_argument if a system path is not a regular file or a directory.
        //! @return A vector of system paths which match the SearchTerms.
        std::vector<std::filesystem::path>&& search();

        private:

        //! Helper function for search to allow recursive directory searches.
        //!
        //! @param system_path The system path (regular file or directory) to search.
        //! @param result The output vector which will store selected files.
        //! @throws std::invalid_argument if a system path is not a regular file or a directory.
        void add_valid_files(const std::filesystem::path& system_path, std::vector<std::filesystem::path>& result);
    };
}