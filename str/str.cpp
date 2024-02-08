#include "str.hpp"


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

kpt::str::operator char const*() const {
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


kpt::str::str(char const*value) {
    kpt::str::memory = value;
}
kpt::str& kpt::str::operator=(char const*value) {
    kpt::str::memory = value;
    return *this;
}
kpt::str kpt::str::operator+(char const*value) {
    return kpt::str::memory + kpt::str(value).memory;
}
kpt::str& kpt::str::operator+=(char const*value) {
    kpt::str::memory = kpt::str::memory + kpt::str(value).memory;
    return *this;
}
bool kpt::str::operator==(char const*value) {
    if (kpt::str::memory == kpt::str(value).to_cstring()) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(char const*value) {
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

kpt::str::str(const int& value) {
    kpt::int_str_object i;
    kpt::str::memory = i._int_to_string(value);
}
kpt::str& kpt::str::operator=(const int& value) {
    kpt::int_str_object i;
    kpt::str::memory = i._int_to_string(value);
    return *this;
}
kpt::str kpt::str::operator+(const int& value) {
    return kpt::str::memory + kpt::str(value).memory;
}
kpt::str& kpt::str::operator+=(const int& value) {
    kpt::str::memory = kpt::str::memory + kpt::str(value).memory;
    return *this;
}
bool kpt::str::operator==(const int& value) {
    if (kpt::str::memory == kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const int& value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
kpt::str::operator int() const {
    kpt::int_str_object inst = memory;
    return inst._string_to_int();
}


kpt::str::str(const long long int& value) {
    kpt::str::memory = std::to_string(value);
}
kpt::str& kpt::str::operator=(const long long int& value) {
    kpt::str::memory = std::to_string(value);
    return *this;
}
kpt::str kpt::str::operator+(const long long int& value) {
    return kpt::str::memory + std::to_string(value);
}
kpt::str& kpt::str::operator+=(const long long int& value) {
    kpt::str::memory = kpt::str::memory + std::to_string(value);
    return *this;
}
bool kpt::str::operator==(const long long int& value) {
    if (kpt::str::memory == kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const long long int& value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}

kpt::str::operator long long int() const {
    return std::stoll(memory);
}

kpt::str::str(const std::u16string& value) {
    kpt::u16_str_object u;
    kpt::str::memory = u._u16_to_string(value);
}
kpt::str& kpt::str::operator=(const std::u16string& value) {
    kpt::u16_str_object u;
    kpt::str::memory = u._u16_to_string(value);
    return *this;
}
kpt::str kpt::str::operator+(const std::u16string& value) {
    return kpt::str::memory + kpt::str(value).memory;
}
kpt::str& kpt::str::operator+=(const std::u16string& value) {
    kpt::str::memory = kpt::str::memory + kpt::str(value).memory;
    return *this;
}
bool kpt::str::operator==(const std::u16string& value) {
    if (kpt::str::memory == kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}
bool kpt::str::operator!=(const std::u16string& value) {
    if (kpt::str::memory != kpt::str(value).memory) {
        return true;
    } else {
        return false;
    }
}

kpt::str::operator std::u16string() const {
    kpt::u16_str_object u16_s = memory;
    return u16_s._string_to_u16();
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

std::string::const_iterator kpt::str::end() {
    return memory.end();
}
char kpt::str::end_character() {
    return *memory.end();
}
bool kpt::str::is_end(char character_to_be_distinguished) {
    if (*memory.end() == character_to_be_distinguished) {
        return true;
    } else {
        return false;
    }
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
typePrintObject::typePrintObject(const kpt::str& strValue) {
}
typePrintObject::~typePrintObject() {
    std::cout << this->strValue;
}
typePrintObject& typePrintObject::operator<<(const kpt::str& right_side) {
    this->strValue += right_side;
    return *this;
}
typePrintObject& typePrintObject::operator<<(const typePrintObject& right_side) {
    this->strValue += right_side.strValue;
    return *this;
}

typePrintObject print(const kpt::str& Values) {
    typePrintObject p(Values);
    return p;
}
typePrintObject print() {
    typePrintObject p(LF);
    return p;
}
std::ostream& kpt::operator<< (std::ostream& stream, const kpt::str& value) {
    stream << value.memory; // 文字列の内容を出力
    return stream;
}
