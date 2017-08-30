#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T10:07:47
#
#-------------------------------------------------

QT       += core gui network xml widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrueSpeed
TEMPLATE = app


SOURCES += main.cpp \
    core/mainwindow.cpp \
    core/ui/ui-util.cpp \
    core/ui/welcomedialog.cpp \
    core/port/CRingBuffer.cpp \
    core/port/laserparser.cpp \
    core/port/tcpclient.cpp \
    core/rawdata/csvpoc.cpp

HEADERS  += \
    core/mainwindow.h \
    core/ui/ui-util.h \
    core/ui/welcomedialog.h \
    core/port/CRingBuffer.h \
    core/port/laserparser.h \
    core/port/tcpclient.h \
    core/rawdata/csvpoc.h

FORMS    += \
    ui/welcomedialog.ui

INCLUDEPATH += . \
    ./core/ui \
    ./core \
    ./core/port \
    ./core/plot \
    ./core/rawdata

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

