QT += core gui widgets

HEADERS += \
    src/classdiagramscene.h \
    src/model.h \
    src/diagrams.h \
    src/mainwindow.h \

SOURCES += \
    src/classdiagramscene.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mainwindow_tools.cpp \
    src/model.cpp \

FORMS += \
    src/mainwindow.ui

RESOURCES     = res/resources.qrc

# install
target.path = ./install
INSTALLS += target



