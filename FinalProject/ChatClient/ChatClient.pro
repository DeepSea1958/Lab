QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

    SOURCES += \
        chatclient.cpp \
        main.cpp \
        mainwindow.cpp \
    msgstorage.cpp \
        privatechatwidget.cpp   # 新增

    HEADERS += \
        chatclient.h \
        mainwindow.h \
    msgstorage.h \
        privatechatwidget.h     # 新增

    FORMS += \
        mainwindow.ui \
        privatechatwidget.ui    # 新增
# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
