QT += gui
QT += widgets

HEADERS      += diagramwindow.h \
                link.h \
                node.h \
                propertiesdialog.h

SOURCES      += diagramwindow.cpp \
                link.cpp \
                main.cpp \
                node.cpp \
                propertiesdialog.cpp

FORMS         = src/gui/propertiesdialog.ui

RESOURCES     = res/resources.qrc

# install
target.path = ./install
INSTALLS += target

