/** @file activityitem.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "activityitem.h"
#include <QGraphicsLineItem>
#include <QGraphicsScene>


ActivityItem::ActivityItem(double x, double yStart, double yEnd, QGraphicsItem *parent)
    : QGraphicsRectItem(parent), x(x), yStart(yStart), yEnd(yEnd)
{
    setBrush(Qt::white);
    setPen(QPen{Qt::black, 2});

    double len = yEnd-yStart;
    setRect(-thickness/2, 0, thickness, len);
    setPos(x, yStart);
}
