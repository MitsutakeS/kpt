#include "bstring.hpp"

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


kpt::bstr_str_object::bstr_str_object() {
    kpt::bstr_str_object::bstr = SysAllocString(L"\0");
}
kpt::bstr_str_object::bstr_str_object(const BSTR& value) {
    kpt::bstr_str_object::bstr = value;
}
kpt::bstr_str_object::bstr_str_object(const std::string& value) {
    kpt::bstr_str_object::bstr = SysAllocString(kpt::wide_char_object(value)._string_to_wchar());
}
kpt::bstr_str_object::~bstr_str_object() {
    SysFreeString(bstr);
}
void kpt::bstr_str_object::operator=(const BSTR& value) {
    bstr = value;
    return;
}
void kpt::bstr_str_object::operator=(const std::string& value) {
    bstr = this->_string_to_bstr(value);
    return;
}
BSTR kpt::bstr_str_object::_string_to_bstr() {
    return bstr;
}
BSTR kpt::bstr_str_object::_string_to_bstr(const std::string& pre_conv_str) {
    bstr = SysAllocString(kpt::wide_char_object(pre_conv_str)._string_to_wchar());
    return bstr;
}
std::string kpt::bstr_str_object::_bstr_to_string() {
    return wide_char_object((const wchar_t*)bstr)._wchar_to_string();
}
std::string kpt::bstr_str_object::_bstr_to_string(const BSTR& pre_conv_str) {
    return wide_char_object((const wchar_t*)pre_conv_str)._wchar_to_string();
}