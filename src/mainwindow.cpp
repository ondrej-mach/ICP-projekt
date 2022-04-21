#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "classdiagramscene.h"

#include <QFileDialog>
#include <QMessageBox>

#include <string>


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

    Model model;
}

void MainWindow::tabChanged(int index) {
    // if the last tab was clicked
    if (index == ui->tabWidget->count()-1) {
         addSequence();
    }

    Command cmd{Command::SWITCH_TAB, {index}};
    model.applyCommand(cmd);
}


void MainWindow::addSequence() {
    ui->tabWidget->addTab(new QWidget, tr("New Sequence"));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
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
}

void MainWindow::on_actionSave_triggered() {
    QString path = filename;
    std::string std_path = path.toUtf8().constData();

    model.storeXML(std_path);
}

void MainWindow::on_actionSaveAs_triggered() {
    QString path = QFileDialog::getSaveFileName(this, "Save as");
    std::string std_path = path.toUtf8().constData();

    model.storeXML(std_path);
}
