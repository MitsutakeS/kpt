#ifndef JCON_HPP
#define JCON_HPP

#ifndef EXPORT
#   if defined(_MSC_VER) // Microsoft
#       define EXPORT __declspec(dllexport)
#       define IMPORT __declspec(dllimport)
#   elif defined(__GNUC__) // GCC
#       define EXPORT __attribute__((visibility("default")))
#       define IMPORT
#   else
#       define EXPORT
#       define IMPORT
#       pragma warning Unknown dynamic link import/export semantics.
#   endif /* !_MSC_VER */
#endif /* !EXPORT */

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
