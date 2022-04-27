#ifndef INTERACTIONITEM_H
#define INTERACTIONITEM_H

#include <QGraphicsLineItem>
# include "model.h"

class InteractionItem : public QGraphicsLineItem
{
public:
    InteractionItem(double y, double xStart, double xEnd, QString desc="", Model::Action::Type type=Model::Action::SYNC);

    QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    double y, xStart, xEnd;
    Model::Action::Type type;
    QString desc;
    QPolygonF interactionHead;
};

#endif // INTERACTIONITEM_H
