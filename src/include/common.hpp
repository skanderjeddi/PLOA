#pragma once

#include "proto/common.hpp"

template <class S> class Option {
    private:
        S someValue;
        bool valueSet;
    
    public:
        Option();
        Option(const S&);
        const S& unwrap() const;
        bool hasValue() const;
};

int random(int, int);
