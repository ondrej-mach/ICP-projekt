/** @file seqdiagramscene.h
 *  @brief Graphical scene for showing and editing sequence diagrams.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef SEQDIAGRAMSCENE_H
#define SEQDIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSet>
#include <QtCore>
#include <QtGui>
#include <QMap>
#include <QString>

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

    double entityDistance = 150;
    double actionDistance = 40;

    double gridToX(int n);
    double gridToY(int n);
    //QMap<QString, QGraphicsItem *> entities;
    //QVector<QGraphicsItem *> actions;

};

#endif // SEQDIAGRAMSCENE_H
