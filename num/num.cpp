#include "num.hpp"

kpt::num::num() : memory(0) {
}
kpt::num::~num() {
}
kpt::num::num(const LLint& value) {
    memory = value;
}
kpt::num& kpt::num::operator=(const LLint& value) {
    memory = value;
    return *this;
}
kpt::num::num(const kpt::num& value) {
    memory = value.memory;
}
kpt::num& kpt::num::operator=(const kpt::num& value) {
    memory = value.memory;
    return *this;
}
LLint kpt::num::operator+(const kpt::num& value) {
    return this->memory + value.memory;
}
kpt::num::operator long long int() const {
    return memory;
}
LLint kpt::num::operator!() {
    LLint local_memory = 1;
    for (LLint i = memory; i > 0; i--) {
        local_memory *= i;
    }
    return local_memory;
}


LLint kpt::random() {
    std::random_device ran;
    return ran();
}
LLint kpt::random(LLint min, LLint max) {
    if (min < max) {
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
        std::uniform_int_distribution<LLint> dist(min, max);
        auto variate = std::bind(dist, engine);
        return variate();
    } else {
        return -1;
    }
}
