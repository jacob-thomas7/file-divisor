#pragma once

#include "search.hpp"

namespace file_divisor {
    //! @defgroup filter_macros Filter Presets
    //! A set of commonly used filter selectors.

    //! Generates a Filter selector function which selects files with the given extension.
    //! @ingroup filter_macros
    #define FILE_DIVISOR__FILTER__EXTENSION(ext) [](const std::filesystem::path& path){ return path.extension() == (ext); }

    //! @defgroup sorting_functions Sorting Presets
    //! A set of commonly used sorting comparison functions and other sorting tools.

    //! Sorts files alphabetically by their extension.
    //! @ingroup sorting_functions
    inline SortResult sort_extension(const std::filesystem::path& path1, const std::filesystem::path& path2){
        if(path1.extension() < path2.extension())
            return SortResult::before;
        
        if(path1.extension() > path2.extension())
            return SortResult::after;

        return SortResult::indeterminate;
    }

    //! Sorts files reverse alphabetically by their extension.
    //! @ingroup sorting_functions
    inline SortResult sort_extension_reverse(const std::filesystem::path& path1, const std::filesystem::path& path2){
        if(path1.extension() < path2.extension())
            return SortResult::after;
        
        if(path1.extension() > path2.extension())
            return SortResult::before;

        return SortResult::indeterminate;
    }

    //! Sorts files alphabetically by their stem (filename without extension).
    //! @ingroup sorting_functions
    inline SortResult sort_stem(const std::filesystem::path& path1, const std::filesystem::path& path2){
        if(path1.stem() < path2.stem())
            return SortResult::before;
        
        if(path1.stem() > path2.stem())
            return SortResult::after;

        return SortResult::indeterminate;
    }
}