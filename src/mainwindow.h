/** @file mainwindow.h
 *  @brief Application's main window with all the scenes and tools.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "model.h"
#include "classdiagramscene.h"
#include "seqdiagramscene.h"
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

private slots:
    void reloadData();
    void tabChanged(int index);

    //class diagram tools
    void selectToolMouse();
    void selectToolAssociate();
    void selectToolAggregate();
    void selectToolCompose();
    void selectToolGeneralize();
    void selectToolClass();
    void selectToolDelete();
    //seq. diagram tools
    void selectToolEntity();
    void selectToolActivate();
    void selectToolDeactivate();
    void selectToolCreateMessage();
    void selectToolSyncMessage();
    void selectToolAsyncMessage();
    void selectToolReturnMessage();
    void selectToolDestroyMessage();

    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();

    void undoChange();
    void redoChange();

private:
    Ui::MainWindow *ui;
    QGraphicsView *classDiagramView;
    ClassDiagramScene *classDiagramScene;
    QGraphicsView *seqDiagramView;
    SeqDiagramScene *seqDiagramScene;

    Tool tool;
    QString filename;

    // initialization
    void connectTools();

    void addSequence();
    void changeTool(Tool tool);
};

#endif
