/** @file activityitem.h
 *  @brief Graphical item to indicate activity.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef ACTIVITYITEM_H
#define ACTIVITYITEM_H

#include <QGraphicsRectItem>

class ActivityItem : public QGraphicsRectItem
{
public:
    ActivityItem(double x, double yStart, double yEnd, QGraphicsItem *parent=nullptr);

    double thickness = 10;
    double x, yStart, yEnd;
};

#endif // ACTIVITYITEM_H
