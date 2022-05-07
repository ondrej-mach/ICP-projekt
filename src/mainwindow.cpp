/** @file mainwindow.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "classdiagramscene.h"
#include "seqdiagramscene.h"

#include <QFileDialog>
#include <QMessageBox>
#include <string>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    classDiagramView = new QGraphicsView(this);
    classDiagramScene = new ClassDiagramScene(tool, classDiagramView);
    connect(classDiagramScene, &ClassDiagramScene::modelChanged, this, &MainWindow::reloadData);
    classDiagramView->setScene(classDiagramScene);

    seqDiagramView = new QGraphicsView(this);
    seqDiagramScene = new SeqDiagramScene(tool, seqDiagramView);
    connect(seqDiagramScene, &SeqDiagramScene::modelChanged, this, &MainWindow::reloadData);
    seqDiagramView->setScene(seqDiagramScene);

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
    if (index == ui->tabWidget->count() - 1) {
         model.addSeqDiagram();
    }

    model.changeTab(index);

    reloadData();
}

void MainWindow::reloadData()
{
    // load everything
    ui->actionUndo->setEnabled(model.canUndo());
    ui->actionRedo->setEnabled(model.canRedo());

    //set visibility of toolbars
    if (model.getTabIndex() > 0) {
        ui->seqWidget->setVisible(true);
        ui->classWidget->setVisible(false);
    }
    else {
        ui->seqWidget->setVisible(false);
        ui->classWidget->setVisible(true);
    }

    // load stuff on tabs
    ui->tabWidget->blockSignals(true);

    ui->tabWidget->clear();
    ui->tabWidget->addTab(classDiagramView, "Class Diagram");

    int currentTab = model.getTabIndex();
    // Filthy hack to set just one sequential scene always on the selected tab
    auto diagrams = model.getSeqDiagrams();
    bool sdViewUsed = false;
    for (unsigned i=0; i < diagrams.size(); i++) {
        auto name = diagrams[i];
        if (int(i) == currentTab-1) {
            ui->tabWidget->addTab(seqDiagramView, QString::fromStdString(name));
            seqDiagramScene->reloadData(QString::fromStdString(name));
            sdViewUsed = true;
        } else {
            ui->tabWidget->addTab(new QWidget(this), QString::fromStdString(name));
        }
    }

    if (currentTab == 0) {
        classDiagramScene->reloadData();
    }

    // Another filthy hack to always keep seqDiagramView displayed.
    // It would cause graphical bugs otherwise
    if (sdViewUsed) {
        ui->tabWidget->addTab(new QWidget(this), "New Sequence");
    } else {
        ui->tabWidget->addTab(seqDiagramView, "New Sequence");
    }

    ui->tabWidget->setCurrentIndex(currentTab);
    ui->tabWidget->blockSignals(false);
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

