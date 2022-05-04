/** @file lifelineitem.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "lifelineitem.h"
#include <QPointF>
#include <QGraphicsScene>
#include <QPainter>

LifeLineItem::LifeLineItem(double x, double yStart, double yEnd, QString name, QGraphicsItem *parent)
    : QGraphicsItem(parent), x(x), yStart(yStart), yEnd(yEnd), name(name) {


    setPos(QPointF(x, yStart));
}

QPainterPath LifeLineItem::shape() const {
    QPainterPath path;
    path.addPolygon(QRectF(-rectWidth/2, -rectHeight, rectWidth, rectHeight));
    return path;
}

void LifeLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(brush);
    //setFlags(QGraphicsItem::ItemIsMovable);

    // Draw the box with name
    QRectF nameBox = QRectF(-rectWidth/2, -rectHeight, rectWidth, rectHeight);
    painter->drawRect(nameBox);
    painter->drawText(nameBox, Qt::AlignCenter, name);

    // Draw the line
    pen.setWidth(5);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    painter->drawLine(QPointF(0,0), QPointF(0, yEnd-yStart));

}

QRectF LifeLineItem::boundingRect() const {
    double lineLength = yEnd-yStart;
    return QRectF(-rectWidth/2, -rectHeight, rectWidth, rectHeight + lineLength);
}
