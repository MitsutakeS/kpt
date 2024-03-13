
#ifndef NUM_HPP
#define NUM_HPP

#include <random>
#include <vector>
#include <iostream>
#include <functional>

typedef long long int LLint;
typedef long double Ldouble;
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
    class sum {
        private:
            Ldouble memory;
        public:
            sum();
            ~sum();

            sum(const sum& value);
            const sum& operator= (const sum& value);

            sum(const LLint& value);
            const sum& operator=(const LLint& value);

            sum(const Ldouble& value);
            const sum& operator=(const Ldouble& value);

            Ldouble add(const Ldouble value);
            Ldouble show(const Ldouble value);
    };
}
#endif /* !NUM_HPP */
