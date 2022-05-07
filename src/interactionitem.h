/** @file interactionitem.h
 *  @brief Graphical item for arrows in sequence diagram.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef INTERACTIONITEM_H
#define INTERACTIONITEM_H

#include <QGraphicsLineItem>
# include "model.h"

class InteractionItem : public QGraphicsLineItem
{
public:
    InteractionItem(double y, double xStart, double xEnd, QString desc, Model::Action::Type type=Model::Action::SYNC, QString from="", QString to="", int index=0);

    // black magic DO NOT TOUCH
    enum { Type = UserType + 18 };
    int type() const override { return Type; }

    QString from, to;
    int index;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    /** @brief Gets position of this entity.
     *  @param item Entity whose position we want.
     *  @return Returns position of this entity.
     */
    QVector<double> getCoords(InteractionItem *item);

private:
    double y, xStart, xEnd;
    Model::Action::Type intType;
    QString desc;
    QPolygonF interactionHead;
};

#endif // INTERACTIONITEM_H
