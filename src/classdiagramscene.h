#ifndef CLASSDIAGRAMSCENE_H
#define CLASSDIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QSet>
#include <QtCore>
#include <QtGui>
#include "classgraphicsitem.h"
#include "model.h"

class ClassDiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ClassDiagramScene(QObject *parent = nullptr, Model *model = nullptr);
    ~ClassDiagramScene();

private:
    QMap<QString, QGraphicsItem *> nodes;
    QSet<QGraphicsItem *> links;
    void reloadData(Model *m);
    Model *model;
};

#endif // CLASSDIAGRAMSCENE_H
