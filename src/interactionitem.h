#ifndef INTERACTIONITEM_H
#define INTERACTIONITEM_H

#include <QGraphicsLineItem>

class InteractionItem : public QGraphicsLineItem
{
public:
    InteractionItem(double y, double xStart, double xEnd);

    QRectF boundingRect() const;
    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    double y, xStart, xEnd;
};

#endif // INTERACTIONITEM_H
