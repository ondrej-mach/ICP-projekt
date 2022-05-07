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
    ~SeqDiagramScene();

    /** @brief Reloads data from model, puts them onto scene.
     *  @return Void.
     */
    void reloadData(QString name);

    /** @brief Gets sequence diagram name.
     *  @param scene The diagram to be named.
     *  @return Returns name of the sequence diagram.
     */
    QString getName(SeqDiagramScene *scene);

    /** @brief Marks item.
     *  @param lli The item to be marked.
     *  @return Void.
     */
    void markItem(LifeLineItem *lli);

public slots:
    void openEditDialog();

signals:
    void modelChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Tool &tool;
    // temporary line when connecting
    QGraphicsLineItem *line;

    double entityDistance = 150;
    double actionDistance = 40;

    double gridToX(int n);
    double gridToY(int n);

    QMap<QString, LifeLineItem *> entities;
    QVector<InteractionItem *> actions;
    QString diagramName;

    LifeLineItem *markedItem;
    QMenu *entityEditMenu; // edit menu for entities
};

#endif // SEQDIAGRAMSCENE_H
