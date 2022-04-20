#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

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
    void loadFile(QString &filename);
    void saveFile(QString &filename);

    void selectToolMouse();
    void selectToolAssociate();
    void selectToolAggregate();
    void selectToolCompose();
    void selectToolGeneralize();
    void selectToolClass();


private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    ClassDiagramScene *classDiagramScene;

    Tool tool;

    // initialization
    void connectTools();

    void addSequence();
    void changeTool(Tool tool);

};

#endif
