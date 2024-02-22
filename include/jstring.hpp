#ifndef JSTRING_HPP
#define JSTRING_HPP 1
#if __has_include(<jni.h>)
#define JNI_H
#include <jni.h>
#include <string>
namespace kpt {
/*
javaの文字列 <==> C++文字列への相互変換
str classで自動で管理。
変換する関数はここのpublicで定義しています
jni.hを使用しています
*/
    class java_env_object {
        private:
            JNIEnv*env;
            jstring jstr;
        public:
            java_env_object();
            java_env_object(const jstring& value);
            java_env_object(const std::string& value);
            ~java_env_object();
            void operator=(const jstring& value);
            void operator=(const std::string& value);
            jstring _string_to_jstring();
            jstring _string_to_jstring(const std::string& pre_conv_str);
            std::string _jstring_to_string();
            std::string _jstring_to_string(const jstring& pre_conv_jstr);
    };
}
#endif/* __has_include(<jni.h>) */
#endif/* JSTRING_HPP */