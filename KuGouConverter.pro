QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = KuGouConverter
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

win32 {
    CONFIG(release, debug|release) {
        DESTDIR = $$PWD/release
        OBJECTS_DIR = $$PWD/build/object
        MOC_DIR = $$PWD/build/moc
        RCC_DIR = $$PWD/build/rcc
        UI_DIR = $$PWD/build/uic
    }

    CONFIG(debug, debug|release) {
        DESTDIR = $$PWD/build
        OBJECTS_DIR = $$PWD/build/object
        MOC_DIR = $$PWD/build/moc
    }
}

!win32 {
    DESTDIR = $$PWD/build
    OBJECTS_DIR = $$PWD/build/object
    MOC_DIR = $$PWD/build/moc
}

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/decrypt/decrypt_global.cpp \
    src/decrypt/kgm_mask_table.cpp \
    src/decrypt/kgm_decrypt.cpp \
    src/decrypt/kgg_decrypt.cpp \
    src/decrypt/crypto_util.cpp \
    src/ui/filewidget.cpp \
    src/ui/convertthread.cpp \
    src/ui/stylesheet.cpp \
    src/ui/dropzone.cpp \
    src/ui/progresspanel.cpp \
    src/models/filemodel.cpp \
    src/utils/fileutil.cpp \
    src/utils/audioinfo.cpp \
    src/utils/stringutil.cpp

HEADERS += \
    src/mainwindow.h \
    src/decrypt/decrypt_global.h \
    src/decrypt/kgm_mask_table.h \
    src/decrypt/kgm_decrypt.h \
    src/decrypt/kgg_decrypt.h \
    src/decrypt/crypto_util.h \
    src/ui/filewidget.h \
    src/ui/convertthread.h \
    src/ui/stylesheet.h \
    src/ui/dropzone.h \
    src/ui/progresspanel.h \
    src/models/filemodel.h \
    src/utils/fileutil.h \
    src/utils/audioinfo.h \
    src/utils/stringutil.h

FORMS += \
    src/mainwindow.ui \
    src/ui/filewidget.ui

RESOURCES += \
    resources.qrc

RC_ICONS = resources/icons/app.ico

INCLUDEPATH += src
