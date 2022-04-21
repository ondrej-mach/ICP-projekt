QT += core gui widgets

HEADERS += \
    src/classdiagramscene.h \
    src/classgraphicsitem.h \
    src/linkgraphicsitem.h \
    src/model.h \
    src/mainwindow.h \
    src/viewdata.h

SOURCES += \
    src/classdiagramscene.cpp \
    src/classgraphicsitem.cpp \
    src/linkgraphicsitem.cpp \
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



