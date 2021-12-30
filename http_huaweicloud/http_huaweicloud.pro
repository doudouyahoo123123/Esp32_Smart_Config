#-------------------------------------------------
#
# Project created by QtCreator 2021-11-08T14:50:31
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = http_huaweicloud
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    Huawei_cloud/hmacsha256.cpp \
    Huawei_cloud/https_post.cpp \
    Huawei_cloud/json_datas.cpp \
    ESP32/CRC/crc_8_maxim.cpp \
    ESP32/protocol/datacode.cpp \
    ESP32/protocol/datumcode.cpp \
    ESP32/protocol/guidecode.cpp \
    ESP32/Tcp/tcp_server.cpp \
    ESP32/Udp/udp_broadcast.cpp

HEADERS += \
        widget.h \
    Huawei_cloud/hmacsha256.h \
    Huawei_cloud/https_post.h \
    Huawei_cloud/json_datas.h \
    ESP32/CRC/crc_8_maxim.h \
    ESP32/protocol/datacode.h \
    ESP32/protocol/datumcode.h \
    ESP32/protocol/guidecode.h \
    ESP32/Tcp/tcp_server.h \
    ESP32/Udp/udp_broadcast.h

FORMS += \
        widget.ui

CONFIG += mobility
MOBILITY = 

#android: include(./android_openssl-master/openssl.pri)

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../build-http_huaweicloud-Android_for_armeabi_v7a_GCC_4_9_Qt_5_9_5_for_Android_armv7-Debug/libopenssl/libcrypto.so \
        $$PWD/../build-http_huaweicloud-Android_for_armeabi_v7a_GCC_4_9_Qt_5_9_5_for_Android_armv7-Debug/libopenssl/libssl.so
}

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_EXTRA_LIBS = \
        $$PWD../build-http_huaweicloud-Android_for_armeabi_v7a_GCC_4_9_Qt_5_9_5_for_Android_armv7-Debug/libopenssl/libcrypto.so \
        $$PWD../build-http_huaweicloud-Android_for_armeabi_v7a_GCC_4_9_Qt_5_9_5_for_Android_armv7-Debug/libopenssl/libssl.so
}




