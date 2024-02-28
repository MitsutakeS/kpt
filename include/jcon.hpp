#ifndef JCON_HPP
#define JCON_HPP
#include "./json/include/nlohmann/json.hpp"
#include "str.hpp"
#include <map>
#include <vector>
#include <filesystem>

namespace kpt {
    using map = std::map<kpt::str, std::vector<std::vector<kpt::str>>>;
    using map_key = kpt::str;
    using map_value = std::vector<std::vector<kpt::str>>;
    using json = nlohmann::json;
}
#endif /* !JCON_HPP */
