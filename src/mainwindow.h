#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "model.h"
#include "classdiagramscene.h"
#include "tool.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Tool getTool() const;

public slots:
    void reloadData();

private slots:
    void tabChanged(int index);

    void selectToolMouse();
    void selectToolAssociate();
    void selectToolAggregate();
    void selectToolCompose();
    void selectToolGeneralize();
    void selectToolClass();

    void openFile();
    void saveFile();
    void saveFileAs();

    void undoChange();
    void redoChange();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    ClassDiagramScene *classDiagramScene;

    Tool tool;
    QString filename;

    // initialization
    void connectTools();

    void addSequence();
    void changeTool(Tool tool);

};

#endif
