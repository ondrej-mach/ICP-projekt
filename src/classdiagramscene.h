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
    void reloadData(Model &m);
    void setTool(Tool tool);

private:
    QMap<QString, ClassGraphicsItem *> nodes;
    QSet<LinkGraphicsItem *> links;
    Tool tool;

};

#endif // CLASSDIAGRAMSCENE_H
