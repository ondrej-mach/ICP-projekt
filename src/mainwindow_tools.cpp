#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::connectTools() {
    connect(ui->cursorToolButton, &QToolButton::pressed, this, &MainWindow::selectToolMouse);
    connect(ui->associationToolButton, &QToolButton::pressed, this, &MainWindow::selectToolAssociate);
    connect(ui->aggregationToolButton, &QToolButton::pressed, this, &MainWindow::selectToolAggregate);
    connect(ui->compositionToolButton, &QToolButton::pressed, this, &MainWindow::selectToolCompose);
    connect(ui->generalizationToolButton, &QToolButton::pressed, this, &MainWindow::selectToolGeneralize);
    connect(ui->classToolButton, &QToolButton::pressed, this, &MainWindow::selectToolClass);
}

void MainWindow::selectToolMouse() {
    tool = TOOL_MOUSE;
}

void MainWindow::selectToolAssociate() {
    tool = TOOL_ASSOCIATE;
}

void MainWindow::selectToolAggregate() {
    tool = TOOL_AGGREGATE;
}

void MainWindow::selectToolCompose() {
    tool = TOOL_COMPOSE;
}

void MainWindow::selectToolGeneralize() {
    tool = TOOL_GENERALIZE;
}

void MainWindow::selectToolClass() {
    tool = TOOL_CLASS;
}

