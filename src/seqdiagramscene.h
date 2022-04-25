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
    SeqDiagramScene(QObject *parent = nullptr);
    //~SeqDiagramScene();

public slots:
    void setTool(Tool tool);
    void reloadData();

signals:
    void modelChanged();

private:
    Tool tool;

    // temporary line when connecting
    QGraphicsLineItem *line;

};

#endif // SEQDIAGRAMSCENE_H
