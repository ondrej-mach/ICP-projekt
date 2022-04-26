QT += core gui widgets

HEADERS += \
    src/classdiagramscene.h \
    src/classeditdialog.h \
    src/classgraphicsitem.h \
    src/lifelineitem.h \
    src/linkgraphicsitem.h \
    src/model.h \
    src/mainwindow.h \
    src/seqdiagramscene.h \
    src/tool.h

SOURCES += \
    src/classdiagramscene.cpp \
    src/classeditdialog.cpp \
    src/classgraphicsitem.cpp \
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



