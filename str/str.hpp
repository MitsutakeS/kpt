#pragma once
#include "Python310/include/Python.h"/* <== first include */

#define STR_HPP 1
// #include
// #ifdef STR_HPP
    // #define XXX
// #endif
// #ifdef XXX
    // processing
// #endif
/* |^| example |^| */


#define print(values) (std::cout << values << std::endl)
#define FILE_EXISTS ()

#include <string>
#include <cstring>
#include <iostream>
#include <locale>
#include <codecvt>


#include "com/comutil.h"
#include "jstring.hpp"

namespace kpt {
    using std::cout;
    using std::wcout;
    using std::endl;
/*
Python文字列<==>C++文字列との相互変換
継承元クラスはPythonのインタプリンタオブジェクトです。
Py_InitializeEX()を使用。意図的に閉じる場合に気をつけてください.
継承元クラスのコンストラクタ、デストラクタでPythonのインタプリンタを動的に呼び出し、オブジェクトの破棄と同時にインタプリンタを閉じます。
その他の関数群はclass strと同等です(strより簡略化しています)

*/
    class PyInterpreter {
        protected:
            PyInterpreter();
            ~PyInterpreter();
    };
    class python_env_object : public PyInterpreter {
        private:
            //PyObject ===>> PyUnicodeObject
            PyObject*pystr;
            public:
                python_env_object();
                python_env_object(PyObject* value);
                python_env_object(const std::string& value);
                ~python_env_object();
                void pyprint();
                void operator=(PyObject* value);
                void operator=(const std::string& value);
                PyObject* _string_to_pystr();
                PyObject* _string_to_pystr(const std::string cpp_str);
                std::string _pystr_to_string();
                std::string _pystr_to_string(PyObject* py_unicode);
    };

    class bstr_str_object {
        private:
            _bstr_t bstr;
        public:
            bstr_str_object();
            bstr_str_object(const _bstr_t& value);
            bstr_str_object(const std::string& value);
            ~bstr_str_object();
            void operator=(const _bstr_t& value);
            void operator=(const std::string& value);
            _bstr_t _string_to_comstr();
            _bstr_t _string_to_comstr(const std::string& pre_conv_str);
            std::string _comstr_to_string();
            std::string _comstr_to_string(const _bstr_t& pre_conv_str);
    };
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
}
namespace kpt {
    // BigBoss...
    class str {
        private:
            std::string memory;
        public:
            str();

            char operator[](int value);

#if __has_include(<jni.h>)
#define J_N_I 1
            str(const jstring& value);
            operator jstring() const;
            str & operator=(const jstring& value);
            str operator+(const jstring& value);
            str& operator+=(const jstring& value);
            bool operator==(const jstring& value);
            bool operator!=(const jstring& value);
#endif
            str(const str& value);
            operator str() const;
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
            operator const char *() const;
            str& operator=(const char* value);
            str operator+(const char* value);
            str& operator+=(const char* value);
            bool operator==(const char* value);
            bool operator!=(const char* value);

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

            str(const _bstr_t& value);
            str& operator=(const _bstr_t& value);
            str operator+(const _bstr_t&  value);
            str& operator+=(const _bstr_t& value);
            bool operator==(const _bstr_t& value);
            bool operator!=(const _bstr_t& value);

            str(const wchar_t* value);
            str& operator=(const wchar_t* value);
            str operator+(const wchar_t* value);
            str& operator+=(const wchar_t* value);
            bool operator==(const wchar_t* value);
            bool operator!=(const wchar_t* value);



            operator std::string() const;
            operator std::wstring() const;
            operator _bstr_t() const;
            operator const wchar_t*() const;
            operator PyObject*() const;

            size_t size() {
                return memory.size();
            }
            size_t max_size() {
                return memory.max_size();
            }
            std::string to_cstring();

            static int to_one_digit_int(char number);
            friend std::ostream& operator<< (std::ostream& stream, const str& value);
    };
    std::ostream& operator<< (std::ostream& stream, const kpt::str& value);
}
