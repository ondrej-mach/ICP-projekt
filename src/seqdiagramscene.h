#ifndef SEQDIAGRAMSCENE_H
#define SEQDIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QSet>
#include <QtCore>
#include <QtGui>

#include "model.h"
#include "tool.h"

class SeqDiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    SeqDiagramScene(Tool &tool, QObject *parent = nullptr);
    //~SeqDiagramScene();


    void reloadData(QString name);

signals:
    void modelChanged();

private:
    Tool tool;
    QString diagramName;
    // temporary line when connecting
    QGraphicsLineItem *line;

};

#endif // SEQDIAGRAMSCENE_H
