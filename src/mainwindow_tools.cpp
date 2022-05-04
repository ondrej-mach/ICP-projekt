/** @file mainwindow_tools.cpp
 *  @brief Functions related to tools and their switching.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::connectTools() {
    // class diagram tools
    connect(ui->cursorToolButton, &QToolButton::pressed, this, &MainWindow::selectToolMouse);
    connect(ui->associationToolButton, &QToolButton::pressed, this, &MainWindow::selectToolAssociate);
    connect(ui->aggregationToolButton, &QToolButton::pressed, this, &MainWindow::selectToolAggregate);
    connect(ui->compositionToolButton, &QToolButton::pressed, this, &MainWindow::selectToolCompose);
    connect(ui->generalizationToolButton, &QToolButton::pressed, this, &MainWindow::selectToolGeneralize);
    connect(ui->classToolButton, &QToolButton::pressed, this, &MainWindow::selectToolClass);
    connect(ui->deleteButton, &QToolButton::pressed, this, &MainWindow::selectToolDelete);
    // seq. diagram tools
    connect(ui->objectToolButton, &QToolButton::pressed, this, &MainWindow::selectToolObject);
    connect(ui->activateButton, &QToolButton::pressed, this, &MainWindow::selectToolActivate);
    connect(ui->deactivateButton, &QToolButton::pressed, this, &MainWindow::selectToolDeactivate);
    connect(ui->createMessageButton, &QToolButton::pressed, this, &MainWindow::selectToolCreateMessage);
    connect(ui->syncMessageButton, &QToolButton::pressed, this, &MainWindow::selectToolSyncMessage);
    connect(ui->asyncMessageButton, &QToolButton::pressed, this, &MainWindow::selectToolAsyncMessage);
    connect(ui->returnMessageButton, &QToolButton::pressed, this, &MainWindow::selectToolReturnMessage);
    connect(ui->destroyMessageButton, &QToolButton::pressed, this, &MainWindow::selectToolDestroyMessage);
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

void MainWindow::selectToolDelete() {
    tool = TOOL_DELETE;
}

void MainWindow::selectToolObject() {
    tool = TOOL_OBJECT;
}

void MainWindow::selectToolActivate() {
    tool = TOOL_ACTIVATE;
}

void MainWindow::selectToolDeactivate() {
    tool = TOOL_DEACTIVATE;
}

void MainWindow::selectToolCreateMessage() {
    tool = TOOL_CREATE_MESSAGE;
}

void MainWindow::selectToolSyncMessage() {
    tool = TOOL_SYNC_MESSAGE;
}

void MainWindow::selectToolAsyncMessage() {
    tool = TOOL_ASYNC_MESSAGE;
}

void MainWindow::selectToolReturnMessage() {
    tool = TOOL_RETURN_MESSAGE;
}

void MainWindow::selectToolDestroyMessage() {
    tool = TOOL_DESTROY_MESSAGE;
}

