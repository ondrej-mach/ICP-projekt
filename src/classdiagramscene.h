#ifndef CLASSDIAGRAMSCENE_H
#define CLASSDIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QSet>
#include <QtCore>
#include <QtGui>
#include "classgraphicsitem.h"
#include "linkgraphicsitem.h"
#include "model.h"
#include "tool.h"

class ClassDiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ClassDiagramScene(QObject *parent = nullptr);
    ~ClassDiagramScene();
    void reloadData();
    void setTool(Tool tool);

    // callbacks from items
    void itemMoved(ClassGraphicsItem *cgi);
    void markItem(ClassGraphicsItem *cgi);

public slots:
    void itemRemoved();
    void openEditDialog();

signals:
    void modelChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    QMap<QString, ClassGraphicsItem *> nodes;
    QSet<LinkGraphicsItem *> links;
    Tool tool;

    // temporary line when connecting classes
    QGraphicsLineItem *line;

    QMenu *editMenu; // edit menu for classes
    QDialog *editDialog;
    ClassGraphicsItem *markedItem;

};

#endif // CLASSDIAGRAMSCENE_H
