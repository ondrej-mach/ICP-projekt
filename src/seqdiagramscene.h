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
#include "interactionitem.h"
#include "lifelineitem.h"

class SeqDiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    SeqDiagramScene(Tool &tool, QObject *parent = nullptr);
    //~SeqDiagramScene();


    void reloadData(QString name);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    QString getName(SeqDiagramScene *scene);


signals:
    void modelChanged();


private:
    Tool &tool;
    // temporary line when connecting
    QGraphicsLineItem *line;

    double entityDistance = 150;
    double actionDistance = 40;

    double gridToX(int n);
    double gridToY(int n);
    int XtoGrid(double x);
    int YtoGrid(double y);
    QMap<QString, LifeLineItem *> entities;
    QVector<InteractionItem *> actions;
    QString diagramName;
};

#endif // SEQDIAGRAMSCENE_H
