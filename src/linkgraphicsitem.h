/** @file linkgraphicsitem.h
 *  @brief Graphical item for a relationship in class diagram.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

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
#include "model.h"

class LinkGraphicsItem : public QGraphicsLineItem
{

public:
    LinkGraphicsItem(ClassGraphicsItem *from,
                     ClassGraphicsItem *to,
                     Model::LinkRepr::Type linkType=Model::LinkRepr::ASSOCIATION,
                     QGraphicsItem *parent=nullptr);
    ~LinkGraphicsItem();

    QRectF boundingRect() const override;

    /** @brief Sets hitbox of this line.
     *  @return Path with hitbox for deletion.
     */
    QPainterPath shape() const override;
    /** @brief Updates the position of this link after one of classes link is connected to is moved.
     *  @param link Link to be connected to the class.
     *  @return Void.
     */
    void updatePosition();

    ClassGraphicsItem *from;
    ClassGraphicsItem *to;

private:

    QColor myColor = Qt::black;
    QPolygonF linkHead;
    Model::LinkRepr::Type linkType;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // LINKGRAPHICSITEM_H
