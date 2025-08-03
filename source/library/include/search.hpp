#pragma once

#include <filesystem>
#include <functional>
#include <stdexcept>
#include <vector>

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
        Filter(std::function<bool(const std::filesystem::path&)> selector, FilterType type);
    };

    //! The return result of sorting functions between two inputs.
    enum class SortResult {
        before, //!< States that the first input should be sorted before the second.
        indeterminate, //!< States that the sorting function cannot tell the sorted order of the inputs.
        after //!< States that the first input should be sorted after the second.
    };

    //! Stores information on what files to search for.
    class Search {
        public:
        
        //! Stores the top-level system directories to begin searching.
        //! Supports files of type std::filesystem::file_type::regular and std::filesystem::file_type::directory.
        std::vector<std::filesystem::path> system_paths;

        //! Stores multiple Filters to be appiled when searching.
        std::vector<Filter> filters;

        //! Stores sorting functions to be applied when searching.
        //! Sorting occurs with the first function, and only continues to the next if the result is indeterminate,
        //! usually meaning that the property the function uses is the same for both files.
        std::vector<std::function<SortResult(const std::filesystem::path&, const std::filesystem::path&)>> sort_functions;

        public:

        //! Adds a system path to search for files.
        void add_system_path(const std::filesystem::path& path);

        //! Adds a filter to apply when searching for files.
        void add_filter(const std::function<bool(const std::filesystem::path&)>& selector, FilterType type);

        //! Adds a sorting function to apply when searching for files.
        void add_sort_function(const std::function<SortResult(const std::filesystem::path&, const std::filesystem::path&)>& function);

        //! Finds all files that match the given search terms.
        //! Searches in all given system paths, excludes filter matches, and sorts based on the given sorting function.
        //!
        //! @throws std::invalid_argument if a system path is not a regular file or a directory.
        //! @return A vector of system paths which match the SearchTerms.
        std::vector<std::filesystem::path>&& search() const;

        private:

        //! Helper function for search to allow recursive directory searches.
        //!
        //! @param system_path The system path (regular file or directory) to search.
        //! @param result The output vector which will store selected files.
        //! @throws std::invalid_argument if a system path is not a regular file or a directory.
        void add_valid_files(const std::filesystem::path& system_path, std::vector<std::filesystem::path>& result) const;

        //! Helper function to compare two paths by all the given sorting functions.
        //!
        //! @param path The first path to compare.
        //! @param result The output vector which stores already added paths.
        //! @param compare_to_index An index into the result array which gives to the second path to compare.
        //! @return Describes whether the first path should be sorted before or after the second.
        SortResult compare(const std::filesystem::path& path, std::vector<std::filesystem::path>& result, int compare_to_index) const;
    };
}