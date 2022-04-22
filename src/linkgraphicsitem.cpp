#include <QLineF>
#include "linkgraphicsitem.h"

LinkGraphicsItem::LinkGraphicsItem(ClassGraphicsItem *from, ClassGraphicsItem *to) {
    this->from = from;
    this->to = to;
    to->addLink(this);
    from->addLink(this);
}

LinkGraphicsItem::~LinkGraphicsItem() {
    //to->removeLink(this);
    //from->removeLink(this);
}

QRectF LinkGraphicsItem::boundingRect() const
{
    qreal height = to->x() - from->x();
    qreal width = to->y() - from->y();
    QRectF rect = QRectF(from->x()-5, from->y()-5, height+10, width+10);
    return mapRectToScene(rect);
}

void LinkGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brushGray(Qt::gray);
    //painter->fillRect(rect, brushGray);

    painter->drawLine(from->x(), from->y(), to->x(), to->y());
}

void LinkGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}


void LinkGraphicsItem::convertToLinkRepr(Model &m)
{
    Model::LinkRepr linkRepr;
    //linkRepr.from = from;
    //linkRepr.to = to;

    //m.changeClassProperties(, linkRepr);
}

