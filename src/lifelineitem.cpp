#include "lifelineitem.h"
#include <QPointF>
#include <QGraphicsScene>
#include <QPainter>

LifeLineItem::LifeLineItem(double x, double yStart, double yEnd, QString name, QGraphicsItem *parent)
    : QGraphicsItem(parent) {

    setPos(QPointF(x, yStart));
}



void LifeLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (this->isSelected()) {
        QPen pen(Qt::black);
        painter->setPen(pen);
    }
    painter->drawRect(QRectF());
}


