#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "model.h"
#include "classdiagramscene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Tool{
        TOOL_MOUSE,
        TOOL_ASSOCIATE,
        TOOL_AGGREGATE,
        TOOL_COMPOSE,
        TOOL_GENERALIZE,
        TOOL_CLASS,
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

    Model model;
    Tool tool;
    QString filename;

    // initialization
    void connectTools();
    void reloadData();

    void addSequence();
    void changeTool(Tool tool);

};

#endif
