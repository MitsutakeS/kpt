#ifdef _MSC_VER
#pragma comment(lib, "str.lib")
#endif

#ifndef STR_HPP /* include gard */
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
#define FILE_EXISTS ()
#include "pstring.hpp"/* Python_string */
#include "jstring.hpp"/* Javastring */
#include "bstring.hpp"/* wide_string-char and utf-string*/
/* Jstring or Bstring contains #include string */

#include <iostream>

namespace kpt {
    using std::cout;
    using std::wcout;
    using std::endl;
    using std::cerr;
    /* type kpt::str */
    class str {
        private:
            std::string memory;
        public:
            str();
            ~str();
            char operator[](int value);

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

            str(const std::string& value);
            str& operator=(const std::string& value);
            str operator+(const std::string& value);
            str& operator+=(const std::string& value);
            bool operator==(const std::string& value);
            bool operator!=(const std::string& value);

            str(const char* value);
            operator char const*() const;
            str& operator=(char const*value);
            str operator+(char const*value);
            str& operator+=(char const*value);
            bool operator==(char const*value);
            bool operator!=(char const*value);

            str(const char& value);
            operator const char&() const;
            str& operator=(const char& value);
            str operator +(const char& value);
            str& operator+=(const char& value);
            bool operator==(const char& value);
            bool operator!=(const char& value);

            str(PyObject* value);
            str& operator=(PyObject* value);
            str operator+(PyObject* value);
            str& operator+=(PyObject* value);
            bool operator==(PyObject* value);
            bool operator!=(PyObject* value);

            str(const BSTR& value);
            str& operator=(const BSTR& value);
            str operator+(const BSTR&  value);
            str& operator+=(const BSTR& value);
            bool operator==(const BSTR& value);
            bool operator!=(const BSTR& value);

            str(const wchar_t* value);
            str& operator=(const wchar_t* value);
            str operator+(const wchar_t* value);
            str& operator+=(const wchar_t* value);
            bool operator==(const wchar_t* value);
            bool operator!=(const wchar_t* value);

            str(const long long int& value);
            str& operator=(const long long int& value);
            str operator+(const long long int& value);
            str& operator+=(const long long int& value);
            bool operator==(const long long int& value);
            bool operator!=(const long long int& value);

            str(const int& value);
            str& operator=(const int& value);
            str operator+(const int& value);
            str& operator+=(const int& value);
            bool operator==(const int& value);
            bool operator!=(const int& value);

            str(const std::u16string& value);
            str& operator=(const std::u16string& value);
            str operator+(const std::u16string& value);
            str& operator+=(const std::u16string& value);
            bool operator==(const std::u16string& value);
            bool operator!=(const std::u16string& value);


            operator std::string() const;
            operator std::wstring() const;
            operator BSTR() const;
            operator const wchar_t*() const;
            operator PyObject*() const;
            operator int() const;
            operator long long int() const;
            operator std::u16string() const;


            size_t size();
            size_t max_size();
            std::string to_cstring();

            static int to_one_digit_int(char number);
            friend std::ostream& operator<< (std::ostream& stream, const str& value);
    };
    std::ostream& operator<< (std::ostream& stream, const kpt::str& value);
}
#define pend print()
class typePrintObject {
    private:
        kpt::str strValue;
    public:
        typePrintObject(const kpt::str& strValue);
        ~typePrintObject();
        typePrintObject& operator<<(const kpt::str& right_side);
        typePrintObject& operator<<(const typePrintObject& right_side);
};
typePrintObject print(const kpt::str& Values);
typePrintObject print();
#endif
