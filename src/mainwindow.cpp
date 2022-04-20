#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "classdiagramscene.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new QGraphicsView;
    classDiagramScene = new ClassDiagramScene;
    view->setScene(classDiagramScene);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(view, tr("Class Diagram"));
    ui->tabWidget->addTab(new QWidget, tr("New Sequence"));
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    connectTools();
    tool = TOOL_MOUSE;
}

void MainWindow::tabChanged(int index) {
    // if the last tab was clicked
    if (index == ui->tabWidget->count()-1) {
         addSequence();
    }
}

void MainWindow::loadFile(QString &filename) {

}

void MainWindow::saveFile(QString &filename) {

}



void MainWindow::addSequence() {
    ui->tabWidget->addTab(new QWidget, tr("New Sequence"));
}



MainWindow::~MainWindow()
{
    delete ui;
}
