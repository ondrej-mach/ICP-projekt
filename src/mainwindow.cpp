#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "classdiagramscene.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new QGraphicsView;
    setCentralWidget(view);

    classDiagramScene = new ClassDiagramScene;
    view->setScene(classDiagramScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
