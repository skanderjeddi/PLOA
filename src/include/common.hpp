#pragma once

#include "proto/common.hpp"

template <class S> class Option {
    private:
        const S someValue;
        bool valueSet;
    
    public:
        Option();
        Option(const S&);
        const S& unwrap() const;
        bool hasValue() const;
};

int random(int, int);
