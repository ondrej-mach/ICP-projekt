/** @file lifelineitem.h
 *  @brief Graphical item for class' lifetime in sequence diagram.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef LIFELINEITEM_H
#define LIFELINEITEM_H

#include <QGraphicsItem>
#include <qpainterpath.h>

class LifeLineItem : public QGraphicsItem
{
public:
    LifeLineItem(double x, double yStart, double yEnd, QString name, QGraphicsItem *parent=nullptr);

    double rectWidth = 120;
    double rectHeight = 40;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;

    QPainterPath shape() const override;
private:
    double x, yStart, yEnd;
    QString name;

};

#endif // LIFELINEITEM_H
