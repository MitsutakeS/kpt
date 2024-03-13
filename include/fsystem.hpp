#ifndef KPT_FSYSTEM_HPP_
#define KPT_FSYSTEM_HPP_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>


#include "define.hpp"
#include "str.hpp"

#ifndef primary
#   define primary std::vector<kpt::str>
#endif /* !primary */
#ifndef secondary
#   define secondary std::vector<std::vector<kpt::str>>
#endif /* !secondary */

namespace kpt {

    class fsystem {
        private:
            std::filesystem::path filepath;
            kpt::str content;
        public:
            fsystem();
            ~fsystem();
            fsystem(const fsystem& filepath);
            const fsystem& operator= (const fsystem& filepath);

            fsystem(const kpt::str& filepath);
            const fsystem& operator= (const kpt::str& filepath);

            operator const kpt::str() const;
            fsystem(const char& filepath);
            const fsystem& operator= (const char& filepath);

            fsystem(const char* filepath);
            const fsystem& operator= (const char* filepath);
            /* Returns the contents of a file */
            /* Process with the split function. */
            kpt::str load(/* member-filepath */);
            kpt::str load(const std::filesystem::path& filepath);
            std::filesystem::path& path();
            const kpt::str& to_kstr();
            std::vector<kpt::str> split(std::string delimiter);
            std::vector<kpt::str> split(kpt::str &input_value, std::string delimiter);
            friend class srdata;
    };
    class datetime {

    };

    class EXPORT srdata {
        private:
            std::vector<kpt::str> content_memory;
        public:
            srdata();
            ~srdata();
            srdata(const srdata& content);
            const srdata& operator= (const srdata& content);
            const srdata& operator>>(srdata content);
            srdata(const std::vector<kpt::str>);
            const srdata& operator= (const std::vector<kpt::str> content);
            const srdata& operator>>(std::vector<kpt::str>);
            srdata(kpt::str& split_data);
            const srdata& operator= (kpt::str& content);
            const srdata& operator>>(kpt::str content);
            template<typename template_type>
            srdata& setline(template_type value);
    };
}

#endif /* !KPT_FSYSTEM_HPP_ */
