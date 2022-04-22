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
    //LinkGraphicsItem(Model::LinkRepr data);
    LinkGraphicsItem(ClassGraphicsItem *from, ClassGraphicsItem *to);
    ~LinkGraphicsItem();

    QRectF boundingRect() const override;
    void convertToLinkRepr(Model &m);

private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    ClassGraphicsItem *from;
    ClassGraphicsItem *to;
};

#endif // LINKGRAPHICSITEM_H
