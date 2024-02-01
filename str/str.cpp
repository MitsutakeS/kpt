#include "str.hpp"

kpt::PyInterpreter::PyInterpreter() {
    Py_InitializeEx(0);
}
kpt::PyInterpreter::~PyInterpreter() {
    Py_FinalizeEx();
}


kpt::python_env_object::python_env_object() {
    pystr = PyUnicode_FromStringAndSize(NULL, 0);
}
kpt::python_env_object::python_env_object(const std::string& value) {
    pystr = this->_string_to_pystr(value);
}
kpt::python_env_object::python_env_object(PyObject* value) {
    pystr = value;
}
kpt::python_env_object::~python_env_object() {
    Py_DECREF(pystr);
}
/*python文字列を扱った後にのみ有効。
python文字列を出力します(試験的)*/
void kpt::python_env_object::pyprint() {
    if (pystr != PyUnicode_FromStringAndSize(NULL, 0)) {
        const char *utf8_message = PyUnicode_AsUTF8(pystr);
        PySys_WriteStdout(utf8_message);
    } else {
        std::cerr << "Err: The pyprint function is only valid after handling python strings.\n";
    }
}
void kpt::python_env_object::operator=(PyObject* value) {
    pystr = value;
    return;
}
void kpt::python_env_object::operator=(const std::string& value) {
    pystr = this->_string_to_pystr(value);
    return;
}
/*Python/str ==> C++/std::string*/
std::string kpt::python_env_object::_pystr_to_string(PyObject* py_unicode) {
    pystr = py_unicode;
    Py_ssize_t size;
    std::string p = PyUnicode_AsUTF8AndSize(pystr, &size);
    return p;
}
std::string kpt::python_env_object::_pystr_to_string() {
    Py_ssize_t size;
    std::string p = PyUnicode_AsUTF8AndSize(pystr, &size);
    return p;
}
PyObject* kpt::python_env_object::_string_to_pystr() {
    return pystr;
}
// C++/std::string ==> Python/str
PyObject* kpt::python_env_object::_string_to_pystr(const std::string cpp_str) {
    pystr = PyUnicode_FromString(cpp_str.c_str());
    return pystr;
}

kpt::bstr_str_object::bstr_str_object() {
    // デフォルトコンストラクタを呼び出す
    bstr = "0";
}
kpt::bstr_str_object::bstr_str_object(const _bstr_t& value) {
    bstr = value;
}
kpt::bstr_str_object::bstr_str_object(const std::string& value) {
    bstr = this->_string_to_comstr(value);
}
kpt::bstr_str_object::~bstr_str_object() {
    bstr.~_bstr_t();
}
void kpt::bstr_str_object::operator=(const _bstr_t& value) {
    bstr = value;
    return;
}
void kpt::bstr_str_object::operator=(const std::string& value) {
    bstr = this->_string_to_comstr(value);
    return;
}
_bstr_t kpt::bstr_str_object::_string_to_comstr(const std::string& pre_conv_str) {
    bstr = pre_conv_str.c_str();
    return bstr;
}
_bstr_t kpt::bstr_str_object::_string_to_comstr() {
    return bstr;
}
std::string kpt::bstr_str_object::_comstr_to_string(const _bstr_t& pre_conv_str) {
    return static_cast<const char*>(pre_conv_str);
}
std::string kpt::bstr_str_object::_comstr_to_string() {
    return static_cast<const char*>(bstr);
}

kpt::wide_char_object::wide_char_object() {
    const wchar_t* wct;
}
kpt::wide_char_object::wide_char_object(const std::string& value) {
    wct = _string_to_wchar(value);
}
void kpt::wide_char_object::operator=(const wchar_t* value) {
    wct = value;
    return;
}
void kpt::wide_char_object::operator=(const std::string& value) {
    wct = this->_string_to_wchar(value);
    return;
}
kpt::wide_char_object::wide_char_object(const wchar_t* value) {
    size_t len = wcslen(value) + 1; // 文字列の長さにNULL文字分を加える
    wchar_t *w = new wchar_t[len]; // メモリ領域を確保
    wcsncpy(w, value, len); // 文字列をコピー
}

kpt::wide_char_object::~wide_char_object() {
}
const wchar_t *kpt::wide_char_object::_string_to_wchar() {
    return wct;
}
const wchar_t *kpt::wide_char_object::_string_to_wchar(const std::string& value) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(value);
    wct = wstr.c_str();
    return wct;
}
std::string kpt::wide_char_object::_wchar_to_string(const wchar_t* value) {
    std::wstring wstr = value;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string s = converter.to_bytes(wstr);
    return s;
}
std::string kpt::wide_char_object::_wchar_to_string() {
    std::wstring wstr = wct;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string s = converter.to_bytes(wstr);
    return s;
}

class str {
    private:
        std::string memory;

    public:
        str() {
            std::string memory;
            memory = "\0";
        }
        /* 宣言時に代入値がstr型だった際の左辺コピーコンストラクタ */
        str(const str& value) {
            if (this != &value) {
                memory = value.memory;
            } else {
                std::cerr << "Self-assignment: assignments that may break objects.\n";
            }
        }
        /*
        宣言時以外で代入値がstr型だった際の左辺オーバーロード
        右辺から受け取り左辺に自身のオブジェクトを返す
        ====================================================
        Left-hand side overloading when the assigned value is of type str except when declaring
        Returns its own object on the left-hand side.
        */
        str& operator=(const str& value) {
            if (this != &value) {
                memory = value.memory;
            }
            return *this;
        }
        str operator+(const str& value) {
            return str(memory + value.memory);
        }
        str& operator+=(const str& value) {
            memory = memory + value.memory;
            return *this;
        }
        bool operator==(const str& value) {
            if (memory == value.memory) {
                return true;
            } else {
                return false;
            }
        }
        bool operator!=(const str & value) {
            if (memory != value.memory) {
                return true;
            } else {
                return false;
            }
        }
        /*
        左辺が~~型だった際のstr型からの暗黙的な型キャスト
        operator ~~() const {左辺に返す値(左辺の型と等しい型)}
        ====================================================
        Implicit typecast from type str when the left-hand side is of type ~~
        operator ~~() const {value to return on the left-hand side -type equal to the type of the left-hand side-}
        */
        operator std::string() const {
            return memory;
        }

        operator const char*() const {
            return memory.c_str();
        }

        operator _bstr_t() const {
            kpt::bstr_str_object b = memory;
            return b._string_to_comstr();
        }
        operator const wchar_t*() const {
            kpt::wide_char_object w = memory;
            return w._string_to_wchar();
        }
        operator std::wstring() const {
            kpt::wide_char_object w = memory;
            return w._string_to_wchar();
        }
        operator str() const {
            return *this;
        }

        str(const std::string& value) {
            memory = value;
        }
        str& operator=(const std::string& value) {
            memory = value;
            return *this;
        }
        str operator+(const std::string& value) {
            return str(memory + value);
        }
        str& operator+=(const std::string& value) {
            memory = memory + value;
            return *this;
        }
        bool operator==(const std::string& value) {
            if (memory == value) {
                return true;
            } else {
                return false;
            }
        }
        bool operator!=(const std::string& value) {
            if (memory != value) {
                return true;
            } else {
                return false;
            }
        }

        str(const char& value) {
            memory = value;
        }
        str& operator=(const char& value) {
            memory = value;
            return *this;
        }
        str(const char* value) {
            memory = value;
        }
        str& operator=(const char* value) {
            memory = value;
            return *this;
        }
        str operator+(const char& value) {
            return str(memory + str(value).memory);
        }
        str& operator+=(const char& value) {
            memory =  memory + str(value).memory;
            return *this;
        }
        bool operator==(const char& value) {
            if (memory == str(value).to_cstring()) {
                return true;
            } else {
                return false;
            }
        }
        bool operator!=(const char& value) {
            if (memory != str(value).memory) {
                return true;
            }  else {
                return false;
            }
        }
        str(const jstring& value) {
            kpt::java_env_object v;
            memory = v._jstring_to_string(value);
        }
        operator jstring() const {
            kpt::java_env_object v = memory;
            return v._string_to_jstring();
        }
        str& operator=(const jstring& value) {
            kpt::java_env_object v;
            memory = v._jstring_to_string(value);
            return *this;
        }

        operator PyObject*() const {
            kpt::python_env_object p = memory;
            return p._string_to_pystr();
        }


        str(PyObject* value) {
            kpt::python_env_object p;
            memory = p._pystr_to_string(value);
        }
        str& operator=(PyObject* value) {
            memory = str(value).memory;
            return *this;
        }
        str operator+(PyObject* value) {
            return memory + str(value).memory;
        }
        str& operator+=(PyObject* value) {
            memory = memory + str(value).memory;
            return *this;
        }
        bool operator==(PyObject* value) {
            if (memory == str(value).memory) {
                return true;
            } else {
                return false;
            }
        }
        bool operator!=(PyObject* value) {
            if (memory != str(value).memory) {
                return true;
            } else {
                return false;
            }
        }

        str(const _bstr_t& value) {
            kpt::bstr_str_object b;
            memory = b._comstr_to_string(value);
        }
        str& operator=(const _bstr_t& value) {
            kpt::bstr_str_object b;
            memory = b._comstr_to_string(value);
            return *this;
        }
        str(const wchar_t* value) {
            kpt::wide_char_object w;
            memory = w._wchar_to_string(value);
        }
        str& operator=(const wchar_t* value) {
            kpt::wide_char_object w;
            memory = w._wchar_to_string(value);
            return *this;
        }
        ~str() {
        }
        std::string to_cstring() {
            return memory;
        }
        size_t size() {
            return memory.size();
        }
        size_t max_size() {
            return memory.max_size();
        }
        char operator[](int value) {
            return memory[value];
        }
        str split(const char& LiteralString) {
            return *this;
        }
        static int to_int(char number) {
            str n = number;
            if (n.size() == 1) {
                return number - '0';
            } else {
                return;
            }
        }

        friend std::ostream& operator<< (std::ostream& stream, const str& value);
    protected:

};
std::ostream& operator<< (std::ostream& stream, const str& value) {
    stream << value.memory; // 文字列の内容を出力
    return stream; // ストリームを返す
}
int main(int argc, char* argv[]) {
    std::cout << str::to_int('12') << std::endl;
    return 0;
}