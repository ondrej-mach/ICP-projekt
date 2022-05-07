/** @file lifelineitem.h
 *  @brief Graphical item for class' lifetime in sequence diagram.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef LIFELINEITEM_H
#define LIFELINEITEM_H

#include <QGraphicsItem>
#include <qpainterpath.h>
#include "model.h"

class LifeLineItem : public QGraphicsItem
{
public:
    LifeLineItem(double x, double yStart, double yEnd, QString name, bool inClassDiag=false, QMenu *contextMenu=nullptr, QGraphicsItem *parent=nullptr);

    // black magic DO NOT TOUCH
    enum { Type = UserType + 17 };
    int type() const override { return Type; }

    bool inClassDiag;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    /** @brief Gets the name of this entity.
     *
     *  @return Returns name of this entity.
     */
    QString getName();

    /** @brief Gets position of this entity.
     *  @param item Entity whose position we want.
     *  @return Returns position of this entity.
     */
    QVector<double> getCoords(LifeLineItem *item);

private:
    double x, yStart, yEnd;
    double rectWidth = 120;
    double rectHeight = 40;
    QString name;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QMenu *myContextMenu;
};

#endif // LIFELINEITEM_H
