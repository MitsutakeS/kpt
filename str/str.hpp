
#ifndef STR_HPP /* include gard */

#include "Python310/include/Python.h"/* <== first include */

#pragma comment(lib, "Python310/libs/python310.lib")
/*
#ifdef STR_HPP
    process
#endif
(sample)
*/
#define STR_HPP 1


#define print(values) (std::cout << values << std::endl)
#define FILE_EXISTS ()

#ifndef GARD_STRING
#define GARD_STRING
    #include <string>
#endif
#include "jstring.hpp"/* Javastring */
#include "bstring.hpp"/* wide_string-char */


#include <iostream>



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

}
namespace kpt {
    // BigBoss...
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



            operator std::string() const;
            operator std::wstring() const;
            operator BSTR() const;
            operator const wchar_t*() const;
            operator PyObject*() const;

            size_t size();
            size_t max_size();
            std::string to_cstring();

            static int to_one_digit_int(char number);
            friend std::ostream& operator<< (std::ostream& stream, const str& value);
    };
    std::ostream& operator<< (std::ostream& stream, const kpt::str& value);
}
#endif
