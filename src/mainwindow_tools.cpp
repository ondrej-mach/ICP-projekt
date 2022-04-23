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
    this->tool = TOOL_MOUSE;
    classDiagramScene->setTool(TOOL_MOUSE);
}

void MainWindow::selectToolAssociate() {
    this->tool = TOOL_ASSOCIATE;
    classDiagramScene->setTool(TOOL_ASSOCIATE);
}

void MainWindow::selectToolAggregate() {
    this->tool = TOOL_AGGREGATE;
    classDiagramScene->setTool(TOOL_AGGREGATE);
}

void MainWindow::selectToolCompose() {
    this->tool = TOOL_COMPOSE;
    classDiagramScene->setTool(TOOL_COMPOSE);
}

void MainWindow::selectToolGeneralize() {
    this->tool = TOOL_GENERALIZE;
    classDiagramScene->setTool(TOOL_GENERALIZE);
}

void MainWindow::selectToolClass() {
    this->tool = TOOL_CLASS;
    classDiagramScene->setTool(TOOL_CLASS);
}

