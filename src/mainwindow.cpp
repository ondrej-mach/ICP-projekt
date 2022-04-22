#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "classdiagramscene.h"

#include <QFileDialog>
#include <QMessageBox>

#include <string>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    Model model;

    ui->setupUi(this);
    view = new QGraphicsView(this);
    classDiagramScene = new ClassDiagramScene(view);
    view->setScene(classDiagramScene);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(view, tr("Class Diagram"));
    ui->tabWidget->addTab(new QWidget, tr("New Sequence"));
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undoChange);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redoChange);

    connectTools();
    tool = TOOL_MOUSE;

    // load data into all elements from model
    reloadData();
}

void MainWindow::tabChanged(int index) {
    // if the last tab was clicked
    if (index == ui->tabWidget->count()-1) {
         addSequence();
    }
    model.changeTab(index);
    reloadData();
}

void MainWindow::reloadData()
{
    // load everything
    ui->actionUndo->setEnabled(model.canUndo());
    ui->actionRedo->setEnabled(model.canRedo());

    ui->tabWidget->blockSignals(true);
    ui->tabWidget->setCurrentIndex(model.getTabIndex());
    ui->tabWidget->blockSignals(false);

    classDiagramScene->reloadData(model);
}

void MainWindow::addSequence() {
    ui->tabWidget->addTab(new QWidget, tr("New Sequence"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile() {
    QString path = QFileDialog::getOpenFileName(this, "Open file");
    std::string std_path = path.toUtf8().constData();

    try {
        model.loadXML(std_path);
        filename = path;

    } catch (...) {
        QMessageBox msgBox;
        msgBox.setText("Invalid file format");
        msgBox.exec();
    }
    reloadData();
}

void MainWindow::saveFile() {
    if (filename == "") {
        saveFileAs();
        return;
    }

    QString path = filename;
    std::string std_path = path.toUtf8().constData();
    model.storeXML(std_path);
}

void MainWindow::saveFileAs() {
    QString path = QFileDialog::getSaveFileName(this, "Save as");
    if (path != "") {
        std::string std_path = path.toUtf8().constData();
        model.storeXML(std_path);
    }
}

void MainWindow::undoChange()
{
    model.undo();
    reloadData();
}

void MainWindow::redoChange()
{
    model.redo();
    reloadData();
}

