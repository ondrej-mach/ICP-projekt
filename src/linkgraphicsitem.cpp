#include <QLineF>
#include "linkgraphicsitem.h"

LinkGraphicsItem::LinkGraphicsItem(QGraphicsItem *src, QGraphicsItem *dst)
{
    from = src;
    to = dst;
    //connect(src, &QGraphicsItem::dragMoveEvent, this, &LinkGraphicsItem::refresh);
}

QRectF LinkGraphicsItem::boundingRect() const
{
    qreal height = to->x() - from->x();
    qreal width = to->y() - from->y();
    QRectF rect = QRectF(from->x(), from->y(), height, width);
    return mapRectToScene(rect);
}

void LinkGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brushGray(Qt::gray);
    painter->fillRect(rect, brushGray);
    painter->setBrush(brushGray);
    painter->drawLine(from->x(), from->y(), to->x(), to->y());
}

void LinkGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void LinkGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void LinkGraphicsItem::refresh()
{
    update();
}

