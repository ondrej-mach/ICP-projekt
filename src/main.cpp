/** @file main.cpp
 *  @brief The entry point to the application.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

/** @mainpage ICP projekt
 *  This is a project for ICP course at VUT FIT.
 *  It's an app for editing UML diagrams written in C++.
 *  App is using Qt toolkit for its graphical interface.
 *  It can read and save custom XML files.
 *  The editor supports one class diagram and multiple sequence diagrams.
 *
 */

#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
