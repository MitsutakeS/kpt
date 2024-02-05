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




kpt::str::str() {
    std::string memory;
    memory = "\0";
}

/* 宣言時に代入値がstr型だった際の左辺コピーコンストラクタ */
kpt::str::str(const str& value) {
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
kpt::str& kpt::str::operator=(const kpt::str& value) {
    if (this != &value) {
        memory = value.memory;
    }
    return *this;
}
kpt::str kpt::str::operator+(const kpt::str& value) {
    return str(memory + value.memory);
}
kpt::str& kpt::str::operator+=(const kpt::str& value) {
    memory = memory + value.memory;
    return *this;
}
bool kpt::str::operator==(const kpt::str& value) {
    if (memory == value.memory) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const kpt::str& value) {
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
kpt::str::operator std::string() const {
    return kpt::str::memory;
}

kpt::str::operator const char*() const {
    return this->memory.c_str();
}

kpt::str::operator BSTR() const {
    kpt::bstr_str_object b = memory;
    return b._string_to_bstr();
}
kpt::str::operator const wchar_t*() const {
    kpt::wide_char_object w = kpt::str::memory;
    return w._string_to_wchar();
}
kpt::str::operator std::wstring() const {
    kpt::wide_char_object w = kpt::str::memory;
    return w._string_to_wchar();
}


kpt::str::str(const std::string& value) {
    kpt::str::memory = value;
}
kpt::str& kpt::str::operator=(const std::string& value) {
    kpt::str::memory = value;
    return *this;
}
kpt::str kpt::str::operator+(const std::string& value) {
    return kpt::str(kpt::str::memory + value);
}
kpt::str& kpt::str::operator+=(const std::string& value) {
    kpt::str::memory = kpt::str::memory + value;
    return *this;
}
bool kpt::str::operator==(const std::string& value) {
    if (kpt::str::memory == value) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const std::string& value) {
    if (kpt::str::memory != value) {
        return true;
    } else {
        return false;
    }
}


kpt::str::str(const char* value) {
    kpt::str::memory = value;
}
kpt::str& kpt::str::operator=(const char* value) {
    kpt::str::memory = value;
    return *this;
}
kpt::str kpt::str::operator+(const char* value) {
    return kpt::str::memory + kpt::str(value).memory;
}
kpt::str& kpt::str::operator+=(const char* value) {
    kpt::str::memory = kpt::str::memory + kpt::str(value).memory;
    return *this;
}
bool kpt::str::operator==(const char* value) {
    if (kpt::str::memory == kpt::str(value).to_cstring()) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const char* value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    }  else {
        return false;
    }
}
kpt::str::str(const char& value) {
    kpt::str::memory = value;
}
kpt::str::operator const char&() const {
    return *kpt::str::memory.c_str();
}
kpt::str& kpt::str::operator=(const char& value) {
    kpt::str::memory = value;
    return *this;
}
kpt::str kpt::str::operator+(const char& value) {
    return kpt::str(memory + kpt::str(value).memory);
}
kpt::str& kpt::str::operator+=(const char& value) {
    kpt::str::memory =  kpt::str::memory + kpt::str(value).memory;
    return *this;
}
bool kpt::str::operator==(const char& value) {
    if (kpt::str::memory == kpt::str(value).to_cstring()) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const char& value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    }  else {
        return false;
    }
}
#ifdef J_N_I/* JNIが環境に無い場合はコンパイルしない */
    kpt::str::str(const jstring& value) {
        kpt::java_env_object v;
        kpt::str::memory = v._jstring_to_string(value);
    }
    kpt::str::operator jstring() const {
        kpt::java_env_object v = memory;
        return v._string_to_jstring();
    }
    kpt::str& kpt::str::operator=(const jstring& value) {
        kpt::java_env_object v;
        memory = v._jstring_to_string(value);
        return *this;
    }
    kpt::str kpt::str::operator+(const jstring& value) {
        return kpt::str::memory + str(value).memory;
    }
    kpt::str& kpt::str::operator+=(const jstring& value) {
        kpt::str::memory = kpt::str::memory + str(value).memory;
        return *this;
    }
    bool kpt::str::operator==(const jstring& value) {
        if (kpt::str::memory == kpt::str(value).to_cstring()) {
            return true;
        } else {
            return false;
        }
    }
    bool kpt::str::operator!=(const jstring& value) {
        if (kpt::str::memory != kpt::str(value).memory) {
            return true;
        }  else {
            return false;
        }
    }
#endif
kpt::str::operator PyObject*() const {
    kpt::python_env_object p = kpt::str::memory;
    return p._string_to_pystr();
}


kpt::str::str(PyObject* value) {
    kpt::python_env_object p;
    kpt::str::memory = p._pystr_to_string(value);
}
kpt::str& kpt::str::operator=(PyObject* value) {
    kpt::str::memory = kpt::str(value).memory;
    return *this;
}
kpt::str kpt::str::operator+(PyObject* value) {
    return kpt::str::memory + kpt::str(value).memory;
}
kpt::str& kpt::str::operator+=(PyObject* value) {
    kpt::str::memory = kpt::str::memory + kpt::str(value).memory;
    return *this;
}
bool kpt::str::operator==(PyObject* value) {
    if (kpt::str::memory == kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(PyObject* value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}

kpt::str::str(const BSTR& value) {
    kpt::bstr_str_object b;
    kpt::str::memory = b._bstr_to_string(value);
}
kpt::str& kpt::str::operator=(const BSTR& value) {
    kpt::str::memory = str(value).memory;
    return *this;
}
kpt::str kpt::str::operator+(const BSTR&  value) {
    return kpt::str::memory + str(value).memory;
}
kpt::str& kpt::str::operator+=(const BSTR& value) {
    kpt::str::memory = kpt::str::memory + kpt::str(value).memory;
    return *this;
}

bool kpt::str::operator==(const BSTR& value) {
    if (kpt::str::memory == kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const BSTR& value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
kpt::str::str(const wchar_t* value) {
    kpt::wide_char_object w;
    kpt::str::memory = w._wchar_to_string(value);
}
kpt::str& kpt::str::operator=(const wchar_t* value) {
    kpt::wide_char_object w;
    kpt::str::memory = w._wchar_to_string(value);
    return *this;
}
kpt::str kpt::str::operator+(const wchar_t* value) {
    return kpt::str::memory + kpt::str(value).memory;
}
kpt::str& kpt::str::operator+=(const wchar_t* value) {
    kpt::str::memory = kpt::str::memory + kpt::str(value).memory;
    return *this;
}
bool kpt::str::operator==(const wchar_t* value) {
    if (kpt::str::memory == kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const wchar_t* value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
kpt::str::~str(){
}

std::string kpt::str::to_cstring() {
    return this->memory;
}
size_t kpt::str::size() {
    return this->memory.size();
}
size_t kpt::str::max_size() {
    return this->memory.max_size();
}
char kpt::str::operator[](int value) {
    return this->memory[value];
}

int kpt::str::to_one_digit_int(char number) {
    kpt::str n = number;
    if (n.size() == 1) {
        return number - '0';
    } else {
        std::cerr << "<argument error> You have to pass a single digit number as an argument\n";
        return -1;
    }
}
std::ostream& kpt::operator<< (std::ostream& stream, const kpt::str& value) {
    stream << value.memory; // 文字列の内容を出力
    return stream;
}
int main(int argc, char* argv[]) {
    ;
    return 0;
}