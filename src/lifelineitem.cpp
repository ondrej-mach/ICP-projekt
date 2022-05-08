/** @file lifelineitem.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "lifelineitem.h"
#include "seqdiagramscene.h"

#include <QPointF>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QDialog>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

LifeLineItem::LifeLineItem(double x, double yStart, double yEnd, QString name, bool inClassDiag, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsItem(parent), inClassDiag(inClassDiag), x(x), yStart(yStart), yEnd(yEnd), name(name), myContextMenu(contextMenu) {

    setPos(QPointF(x, yStart));
}

QPainterPath LifeLineItem::shape() const {
    QPainterPath path;
    path.addPolygon(QRectF(-rectWidth/2, -rectHeight, rectWidth, rectHeight));
    return path;
}

QString LifeLineItem::getName()
{
    return name;
}

void LifeLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(brush);

    // Draw the box with name
     if(!inClassDiag) {
        pen.setColor(Qt::red);
        painter->setPen(pen);
    }
    QRectF nameBox = QRectF(-rectWidth/2, -rectHeight, rectWidth, rectHeight);

    painter->drawRect(nameBox);
    painter->drawText(nameBox, Qt::AlignCenter, name);

    // Draw the line
    pen.setWidth(5);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawLine(QPointF(0,0), QPointF(0, yEnd-yStart));

}

QRectF LifeLineItem::boundingRect() const {
    double lineLength = yEnd-yStart;
    return QRectF(-rectWidth/2, -rectHeight, rectWidth, rectHeight + lineLength);
}

void LifeLineItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    // mark myself so i can be deleted or edited
    // not relly the best practice but who cares at this point
    qobject_cast<SeqDiagramScene *>(scene())->markItem(this);

    if (myContextMenu != nullptr) {
        myContextMenu->exec(event->screenPos());
    }
}

QVector<double> LifeLineItem::getCoords(LifeLineItem *item)
{
    return QVector<double>{item->x, item->yStart, item->yEnd};
}
