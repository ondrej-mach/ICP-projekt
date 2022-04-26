#ifndef LIFELINEITEM_H
#define LIFELINEITEM_H

#include <QGraphicsItem>

class LifeLineItem : public QGraphicsItem
{
public:
    LifeLineItem(double x, double yStart, double yEnd, QString name, QGraphicsItem *parent);

    double rectWidth = 100;
    double rectHeight = 30;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
};

#endif // LIFELINEITEM_H
