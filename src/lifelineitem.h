#ifndef LIFELINEITEM_H
#define LIFELINEITEM_H

#include <QGraphicsItem>

class LifeLineItem : public QGraphicsItem
{
public:
    LifeLineItem(double x, double yStart, double yEnd, QString name, QGraphicsItem *parent=nullptr);

    double rectWidth = 120;
    double rectHeight = 40;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;

private:
    double x, yStart, yEnd;
    QString name;

};

#endif // LIFELINEITEM_H
