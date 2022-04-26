#include "interactionitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QPen>

InteractionItem::InteractionItem(double y, double xStart, double xEnd)
    : y(y), xStart(xStart), xEnd(xEnd)
{
    setPos(xStart, y);
    double len = xEnd - xStart;

    QPen pen{Qt::black, 3, Qt::SolidLine};
    setPen(pen);
    setLine(QLineF(QPointF(), QPointF(len,0)));
}


QRectF InteractionItem::boundingRect() const {
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

