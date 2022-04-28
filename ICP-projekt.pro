QMAKE_INCDIR += inc
CONFIG += c++17

QT += core gui widgets

HEADERS += \
    src/activityitem.h \
    src/classdiagramscene.h \
    src/classeditdialog.h \
    src/classgraphicsitem.h \
    src/interactionitem.h \
    src/lifelineitem.h \
    src/linkgraphicsitem.h \
    src/model.h \
    src/mainwindow.h \
    src/seqdiagramscene.h \
    src/tool.h

SOURCES += \
    src/activityitem.cpp \
    src/classdiagramscene.cpp \
    src/classeditdialog.cpp \
    src/classgraphicsitem.cpp \
    src/interactionitem.cpp \
    src/lifelineitem.cpp \
    src/linkgraphicsitem.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mainwindow_tools.cpp \
    src/model.cpp \
    src/seqdiagramscene.cpp

FORMS += \
    src/classeditdialog.ui \
    src/mainwindow.ui

RESOURCES     = res/resources.qrc

# install
target.path = ./install
INSTALLS += target



