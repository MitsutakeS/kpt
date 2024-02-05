#ifndef GARD_STRING
    #define GARD_STRING
    #include <string>
#endif

// include gard
#ifndef BSTRING_HPP
#pragma comment(lib,"msvcrt.lib")
#pragma comment(lib, "msvcprt.lib")
    #define BSTRING_HPP
    #include <windows.h>
    #include <cstring>
    #include <locale>
    #include <codecvt>
    #include <stdlib.h>

namespace kpt {
    class wide_char_object {
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
    class bstr_str_object {
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
}
#endif