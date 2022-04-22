#ifndef LINKGRAPHICSITEM_H
#define LINKGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QString>
#include <QPair>
#include <QGraphicsLineItem>

#include "classgraphicsitem.h"

class LinkGraphicsItem : public QGraphicsItem
{

public:

    LinkGraphicsItem(QGraphicsItem *src, QGraphicsItem *dst);
    QRectF boundingRect() const override;

private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


    QGraphicsItem *from;
    QGraphicsItem *to;

private slots:
    void refresh();
};

#endif // LINKGRAPHICSITEM_H
