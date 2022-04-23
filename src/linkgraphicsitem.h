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

class LinkGraphicsItem : public QGraphicsLineItem
{

public:
    //LinkGraphicsItem(Model::LinkRepr data);
    LinkGraphicsItem(ClassGraphicsItem *from, ClassGraphicsItem *to, QGraphicsItem *parent=nullptr);
    ~LinkGraphicsItem();



    void convertToLinkRepr(Model &m);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void updatePosition();
private:
    ClassGraphicsItem *from;
    ClassGraphicsItem *to;
    QColor myColor = Qt::black;
    QPolygonF linkHead;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // LINKGRAPHICSITEM_H
