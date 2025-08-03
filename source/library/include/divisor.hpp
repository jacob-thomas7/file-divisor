#pragma once

#include "search.hpp"
#include <filesystem>

namespace file_divisor {
    //! A "virtual directory" which allows for file paths to be defined based on custom divisions.
    class Divisor : Search {
        
    };

    class DivisorIterator {
        //! Iterates through a Divisor, or a "virtual directory."
        public:
        
        using iterator_category = std::input_iterator_tag;
        using value_type = std::filesystem::path;
        using difference_type = std::ptrdiff_t;
        using pointer = std::filesystem::path*;
        using reference = std::filesystem::path&;

        DivisorIterator() = default;
    };
}