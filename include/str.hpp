/* 実行できない場合のアドバイス */
/* 実行するときにオプションに以下のコマンドを追加する */

/* -L "./kpt/lib" -lstr -lpython310 -loleaut32*/

/* Javaの環境がある方は別途 -ljvmが必要です*/
/* また、g++が必須であり、C++20推奨です */
/* g++ main.cpp -o main.exe -I "./kpt/include" -L ".kpt/lib" -lstr -lpython310 -loleaut32*/

/* kptディレクトリを%KPT_HOME%に、kpt/binディレクトリを環境変数に追加すると便利です */

/* "chcp 65001"をsetting.jsonの"PowerShell":{"args": [here]} hereの部分に追加してください */
/* そこまでできたら以下のようにしてもcode runnerが起動します */
/* "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt -L \"$Env:JAVA_HOME/lib\" -L \"$Env:KPT_HOME/lib\" -L \"$Env:KPT_HOME/include/python310/libs\" -lstr -lpython310 -ljvm -loleaut32 -std=c++20 && $dir$fileNameWithoutExt", */
/* ご参考までに。 */

/* For Windows, For C++20, For mingw64 and g++ */

/* もし環境がVisualStudioだったらpragmaする */
#ifdef _MSC_VER
#   pragma comment(lib, "str.lib")
#   pragma comment(lib, "jvm.lib")
#   pragma comment(lib, "python310.lib")
#   pragma comment(lib, "loleaut32.dll")
#endif

#ifndef STR_HPP /* include gard */

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

/*
#ifdef STR_HPP
    process
#else
    throw()
#endif
(sample)
*/

#define STR_HPP 1
#define SPACE "\x020"
#define INDENT "\t"
#define LF "\n"
#define NULL_COMMAND "\0"
#define ZERO_POINT 0

#define FILE_EXISTS ()

#define KPT(x) kpt::str(x)

#include "pstring.hpp"/* Python_string */
#include "jstring.hpp"/* Javastring */
#include "bstring.hpp"/* wide_string-char and utf-string*/
/* Jstring or Bstring contains #include string */
#include <map>
#include <vector>
#include <iostream>

namespace kpt {

    /* type kpt::str */
    /* const may reject references to member functions */
    class EXPORT str {
        private:
            std::string memory;
        public:
            str();
            ~str();
            char operator[](int value);
/* jniが環境に無ければコンパイルしない */
#ifdef JNI_H

            str(const jstring& value);
            operator jstring() const;
            str & operator=(const jstring& value);
            str operator+(const jstring& value);
            str& operator+=(const jstring& value);
            bool operator==(const jstring& value);
            bool operator!=(const jstring& value);
#endif
            str(const str& value);
            str& operator=(const str& value);
            str operator+(const str& value);
            str& operator+=(const str& value);
            bool operator==(const str& value);
            bool operator!=(const str& value);
            bool operator< (const str& value) const;
            bool operator> (const str& value);
            bool operator>=(const str& value);
            bool operator<=(const str& value);

            str(const std::string& value);
            str& operator= (const std::string& value);
            str  operator+ (const std::string& value);
            str& operator+=(const std::string& value);
            bool operator==(const std::string& value);
            bool operator!=(const std::string& value);
            bool operator< (const std::string& value);
            bool operator> (const std::string& value);
            bool operator>=(const std::string& value);
            bool operator<=(const std::string& value);

            str(const char* value);
            operator char const*() const;
            str& operator= (char const*value);
            str  operator+ (char const*value);
            str& operator+=(char const*value);
            bool operator==(char const*value);
            bool operator!=(char const*value);
            bool operator< (char const* value);
            bool operator> (char const* value);
            bool operator>=(char const* value);
            bool operator<=(char const* value);

            str(const char& value);
            operator const char&() const;
            str& operator= (const char& value);
            str operator + (const char& value);
            str& operator+=(const char& value);
            bool operator==(const char& value);
            bool operator!=(const char& value);
            bool operator< (const char& value);
            bool operator> (const char& value);
            bool operator>=(const char& value);
            bool operator<=(const char& value);

            str(PyObject* value);
            str& operator= (PyObject* value);
            str  operator+ (PyObject* value);
            str& operator+=(PyObject* value);
            bool operator==(PyObject* value);
            bool operator!=(PyObject* value);
            bool operator< (PyObject* value);
            bool operator> (PyObject* value);
            bool operator>=(PyObject* value);
            bool operator<=(PyObject* value);

            str(const BSTR& value);
            str& operator= (const BSTR& value);
            str  operator+ (const BSTR& value);
            str& operator+=(const BSTR& value);
            bool operator==(const BSTR& value);
            bool operator!=(const BSTR& value);
            bool operator< (const BSTR& value);
            bool operator> (const BSTR& value);
            bool operator>=(const BSTR& value);
            bool operator<=(const BSTR& value);

            /* wchar_tよ永遠に・・・ */
            str(const wchar_t* value);
            str& operator= (const wchar_t* value);
            str  operator+ (const wchar_t* value);
            str& operator+=(const wchar_t* value);
            bool operator==(const wchar_t* value);
            bool operator!=(const wchar_t* value);
            bool operator< (const wchar_t* value);
            bool operator> (const wchar_t* value);
            bool operator>=(const wchar_t* value);
            bool operator<=(const wchar_t* value);

            str(const long long int& value);
            str& operator= (const long long int& value);
            str  operator+ (const long long int& value);
            str& operator+=(const long long int& value);
            bool operator==(const long long int& value);
            bool operator!=(const long long int& value);
            bool operator< (const long long int& value);
            bool operator> (const long long int& value);
            bool operator>=(const long long int& value);
            bool operator<=(const long long int& value);

            str(const long double& value);
            str& operator= (const long double& value);
            str  operator+ (const long double& value);
            str& operator+=(const long double& value);
            bool operator==(const long double& value);
            bool operator!=(const long double& value);
            bool operator< (const long double& value);
            bool operator> (const long double& value);
            bool operator>=(const long double& value);
            bool operator<=(const long double& value);

            str(const double& value);
            str& operator= (const double& value);
            str  operator+ (const double& value);
            str& operator+=(const double& value);
            bool operator==(const double& value);
            bool operator!=(const double& value);
            bool operator< (const double& value);
            bool operator> (const double& value);
            bool operator>=(const double& value);
            bool operator<=(const double& value);

            str(const int& value);
            str& operator= (const int& value);
            str  operator+ (const int& value);
            str& operator+=(const int& value);
            bool operator==(const int& value);
            bool operator!=(const int& value);
            bool operator< (const int& value);
            bool operator> (const int& value);
            bool operator>=(const int& value);
            bool operator<=(const int& value);

            str(const std::u16string& value);
            str& operator=(const std::u16string& value);
            str operator+(const std::u16string& value);
            str& operator+=(const std::u16string& value);
            bool operator==(const std::u16string& value);
            bool operator!=(const std::u16string& value);
            bool operator< (const std::u16string& value);
            bool operator> (const std::u16string& value);
            bool operator>=(const std::u16string& value);
            bool operator<=(const std::u16string& value);


            str(const std::u8string& value);
            str& operator=(const std::u8string& value);
            str operator+(const std::u8string& value);
            str& operator+=(const std::u8string& value);
            bool operator==(const std::u8string& value);
            bool operator!=(const std::u8string& value);
            bool operator< (const std::u8string& value);
            bool operator> (const std::u8string& value);
            bool operator>=(const std::u8string& value);
            bool operator<=(const std::u8string& value);

            str(const char16_t *value);
            str& operator= (const char16_t* value);
            str  operator+ (const char16_t* value);
            str& operator+=(const char16_t* value);
            bool operator==(const char16_t* value);
            bool operator!=(const char16_t* value);
            bool operator< (const char16_t* value);
            bool operator> (const char16_t* value);
            bool operator>=(const char16_t* value);
            bool operator<=(const char16_t* value);

            str(const char8_t* value);
            str& operator= (const char8_t* value);
            str  operator+ (const char8_t* value);
            str& operator+=(const char8_t* value);
            bool operator==(const char8_t* value);
            bool operator!=(const char8_t* value);
            bool operator< (const char8_t* value);
            bool operator> (const char8_t* value);
            bool operator>=(const char8_t* value);
            bool operator<=(const char8_t* value);

            operator std::string() const;
            operator std::wstring() const;
            operator BSTR() const;
            operator const wchar_t*() const;
            operator PyObject*() const;

            operator int() const;
            operator long long int() const;
            operator long double() const;
            operator double() const;

            operator const std::u16string() const;
            operator const char16_t*() const;
            operator const std::u8string() const;
            operator const char8_t*() const;

            const char* data();
            size_t size();
            size_t max_size();
            std::string::const_iterator end();
            char get_end_character();
            bool is_end (char character_to_be_distinguished);
            bool is_null();
            const char8_t* to_u8char();
            const char8_t* to_u8char(const kpt::str& value);
            const std::u16string to_u16string();
            const std::string to_cstring();
            const char* to_char();
            double to_double();
            static int to_one_digit_int(char number);
            friend std::ostream& operator<< (std::ostream& stream, const str& value);
            static const std::string to_cstring(const kpt::str& string);
            static const char* to_char(const kpt::str& string);
            kpt::str& swap(kpt::str *value);
    };

    EXPORT std::ostream& operator<< (std::ostream& stream, const kpt::str& value);
}
#endif/* !STR_HPP */
