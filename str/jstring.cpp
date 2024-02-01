#include "jstring.hpp"
#if __has_include(<jni.h>)

kpt::java_env_object::java_env_object() : kpt::java_env_object::jstr(env->NewStringUTF("\0")) {
    env = new JNIEnv;
}
kpt::java_env_object::~java_env_object() {
    env->DeleteLocalRef(jstr);
    delete env;
}
kpt::java_env_object::java_env_object(const jstring& value) {
    jstr = value;
}
void kpt::java_env_object::operator=(const jstring& value) {
    jstr = value;
    return;
}
kpt::java_env_object::java_env_object(const std::string& value) {
    jstr = this->_string_to_jstring(value);
}
void kpt::java_env_object::operator=(const std::string& value) {
    jstr = this->_string_to_jstring(value);
    return;
}
jstring kpt::java_env_object::_string_to_jstring(const std::string& pre_conv_str) {
    jstr = env->NewStringUTF(pre_conv_str.c_str());
    return jstr;
}
jstring kpt::java_env_object::_string_to_jstring() {
    return jstr;
}
std::string kpt::java_env_object::_jstring_to_string(const jstring& pre_conv_jstr) {
    return env->GetStringUTFChars(pre_conv_jstr, NULL);
}
std::string _jstring_to_string() {
    return env->GetStringUTFChars(jstr,NULL);
}
#endif
