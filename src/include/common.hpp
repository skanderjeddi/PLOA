#pragma once

#include "proto/common.hpp"

template <class S> class Option {
    private:
        const S someValue;
        bool valueSet;
    
    public:
        Option();
        Option(const S&);
        /**
         * @brief Unwraps the value of the Option.
         * 
         * @return const S& the value of the Option.
         */
        const S& unwrap() const;
        /**
         * @brief Check if the Option has a value.
         * 
         * @return true if the Option has a value.
         * @return false otherwise.
         */
        bool hasValue() const;
};

/**
 * @brief Generates a random integer between the given bounds.
 * 
 * @return int a random integer between the given bounds (included).
 */
int random(int, int);
