#ifndef PSTRING_HPP
#define PSTRING_HPP 1
#include "Python310/include/Python.h"/* <== first include */
#include <iostream>

namespace kpt {
/*
Python文字列<==>C++文字列との相互変換
継承元クラスはPythonのインタプリンタオブジェクトです。
Py_InitializeEX()を使用。意図的に閉じる場合に気をつけてください.
継承元クラスのコンストラクタ、デストラクタでPythonのインタプリンタを動的に呼び出し、オブジェクトの破棄と同時にインタプリンタを閉じます。
その他の関数群はclass strと同等です(strより簡略化しています)
Python String <==> C++ String
The inherited source class is a Python imprinter object.
Py_InitializeEX(). Be careful when intentionally closing .
The constructor and destructor of the inheriting source class call the Python interprinter dynamically and close the interprinter at the same time the object is destroyed.
Other functions are equivalent to class str (simplified from str).
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
#endif
