#include "jstring.hpp"
#ifdef JNI_H
kpt::java_env_object::java_env_object() : jstr(kpt::java_env_object::env->NewStringUTF("\0")) {
    kpt::java_env_object::env = new JNIEnv;
}
kpt::java_env_object::~java_env_object() {
    kpt::java_env_object::env->DeleteLocalRef(jstr);
    delete kpt::java_env_object::env;
}
kpt::java_env_object::java_env_object(const jstring& value) {
    kpt::java_env_object::jstr = value;
}
void kpt::java_env_object::operator=(const jstring& value) {
    kpt::java_env_object::jstr = value;
    return;
}
kpt::java_env_object::java_env_object(const std::string& value) {
    kpt::java_env_object::jstr = this->_string_to_jstring(value);
}
void kpt::java_env_object::operator=(const std::string& value) {
    kpt::java_env_object::jstr = this->_string_to_jstring(value);
    return;
}
jstring kpt::java_env_object::_string_to_jstring(const std::string& pre_conv_str) {
    kpt::java_env_object::jstr = kpt::java_env_object::env->NewStringUTF(pre_conv_str.c_str());
    return kpt::java_env_object::jstr;
}
jstring kpt::java_env_object::_string_to_jstring() {
    return kpt::java_env_object::jstr;
}
std::string kpt::java_env_object::_jstring_to_string(const jstring& pre_conv_jstr) {
    return kpt::java_env_object::env->GetStringUTFChars(pre_conv_jstr, NULL);
}
std::string kpt::java_env_object::_jstring_to_string() {
    return kpt::java_env_object::env->GetStringUTFChars(kpt::java_env_object::jstr,NULL);
}
#endif
