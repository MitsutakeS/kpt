


// include gard
#ifndef BSTRING_HPP
#define BSTRING_HPP

#   include <windows.h>
#   include <cstring>
#   include <locale>
#   include <codecvt>
#   include <stdlib.h>
#   include <string>

#   include "define.hpp"/* EXPORT */

namespace kpt {
    class EXPORT wide_char_object {
        private:
            const wchar_t* wct;
        public:
            wide_char_object();
            wide_char_object(const wchar_t* value);
            wide_char_object(const std::string& value);
            ~wide_char_object();
            void operator=(const wchar_t* value);
            void operator=(const std::string& value);
            const wchar_t* _string_to_wchar();
            const wchar_t* _string_to_wchar(const std::string& value);
            std::string _wchar_to_string();
            std::string _wchar_to_string(const wchar_t* value);
    };
    class EXPORT bstr_str_object {
        private:
            BSTR bstr;
        public:
            bstr_str_object();
            bstr_str_object(const BSTR& value);
            bstr_str_object(const std::string& value);
            ~bstr_str_object();
            void operator=(const BSTR& value);
            void operator=(const std::string& value);
            BSTR _string_to_bstr();
            BSTR _string_to_bstr(const std::string& pre_conv_str);
            std::string _bstr_to_string();
            std::string _bstr_to_string(const BSTR& pre_conv_str);
    };
    class EXPORT u16_str_object {
        private:
            std::u16string u16;
        public:
            u16_str_object();
            u16_str_object(const std::u16string& value);
            u16_str_object(const std::string& value);
            ~u16_str_object();
            void operator=(const std::u16string& value);
            void operator=(const std::string& value);
            std::u16string _string_to_u16();
            std::u16string _string_to_u16(const std::string& value);
            std::string _u16_to_string();
            std::string _u16_to_string(const std::u16string& value);
    };
    class EXPORT u8_str_object {
        private:
            std::u8string u8;
        public:
            u8_str_object();
            u8_str_object(const std::u8string& value);
            u8_str_object(const std::string& value);
            ~u8_str_object();
            void operator=(const std::u8string& value);
            void operator=(const std::string &value);

            std::u8string _string_to_u8();
            std::u8string _string_to_u8(const std::string& value);
            std::string _u8_to_string();
            std::string _u8_to_string(const std::u8string& value);
    };
    class EXPORT int_str_object {
        private:
            int integer;
        public:
            int_str_object();
            int_str_object(const int& value);
            int_str_object(const std::string& value);
            ~int_str_object();
            void operator=(const int& value);
            void operator=(const std::string& value);
            int _string_to_int();
            int _string_to_int(const std::string& value);
            std::string _int_to_string();
            std::string _int_to_string(const int& value);
    };
}
#endif /* !BSTRING_HPP */