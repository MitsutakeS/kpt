
#ifndef NUM_HPP
#define NUM_HPP

#include <random>
#include <vector>
#include <iostream>
#include <functional>

typedef long long int LLint;
namespace kpt {
    class num {
        private:
            LLint memory;
        public:
            num();
            ~num();
            num& operator=(const LLint& value);
            num(const LLint& value);
            num(const num& value);
            num& operator=(const num& value);
            LLint operator+(const num& value);
            operator long long int() const;
            LLint operator!();
    };
    LLint random();
    LLint random(LLint min, LLint max);
}
#endif
