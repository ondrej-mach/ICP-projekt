#include <QLineF>
#include "linkgraphicsitem.h"

LinkGraphicsItem::LinkGraphicsItem(QGraphicsItem *src, QGraphicsItem *dst)
{
    from = src;
    to = dst;
}

LinkGraphicsItem::LinkGraphicsItem(Model::LinkRepr data)
{

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

void LinkGraphicsItem::convertToLinkRepr(Model &m)
{
    Model::LinkRepr linkRepr;
    linkRepr.from = from;
    linkRepr.to = to;

    //m.changeClassProperties(, linkRepr);
}

