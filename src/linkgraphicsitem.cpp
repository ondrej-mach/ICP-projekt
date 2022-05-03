/** @file linkgraphicsitem.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "linkgraphicsitem.h"
#include "model.h"

#include <QPainter>
#include <QPen>
#include <QtMath>

LinkGraphicsItem::LinkGraphicsItem(ClassGraphicsItem *from, ClassGraphicsItem *to,
                                   Model::LinkRepr::Type linkType,QGraphicsItem *parent)
    : QGraphicsLineItem(parent), from(from), to(to) {

    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    this->linkType = linkType;
    to->addLink(this);
    from->addLink(this);
    setZValue(-1000.0);
}

LinkGraphicsItem::~LinkGraphicsItem() {
    //to->removeLink(this);
    //from->removeLink(this);
}

QRectF LinkGraphicsItem::boundingRect() const {
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath LinkGraphicsItem::shape() const {
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(linkHead);
    return path;
}

void LinkGraphicsItem::updatePosition() {
    QLineF line(mapFromItem(from, 0, 0), mapFromItem(to, 0, 0));
    setLine(line);
}

void LinkGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    //if (from->collidesWithItem(to))
    //    return;

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QLineF centerLine(from->pos(), to->pos());
    QPolygonF endPolygon = to->boundingRect(); // changed
    QPointF p1 = endPolygon.first() + to->pos();
    QPointF intersectPoint;
    for (int i = 1; i < endPolygon.count(); ++i) {
        QPointF p2 = endPolygon.at(i) + to->pos();
        QLineF polyLine = QLineF(p1, p2);
        // TODO QLineF::IntersectionType in modern code
        // polyLine.intersects
        QLineF::IntersectType intersectionType =
            polyLine.intersect(centerLine, &intersectPoint); 
        if (intersectionType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, from->pos()));

    double angle = std::atan2(-line().dy(), line().dx());

    double arg = angle + M_PI / 3;
    QPointF arrowP1 = line().p1() + arrowSize *
                      QPointF(sin(arg), cos(arg));
    arg = angle + M_PI * 2 / 3;
    QPointF arrowP2 = line().p1() + arrowSize *
                      QPointF(sin(arg), cos(arg));
    arg = angle + M_PI / 2;
    QPointF arrowP3 = line().p1() + arrowSize * 2 *
                      QPointF(sin(arg), cos(arg));
    QPointF arrowP4 = line().p1() + arrowSize *
                      QPointF(sin(arg), cos(arg));

    linkHead.clear();

    if (linkType == Model::LinkRepr::AGGREGATION) {
        linkHead << line().p1() << arrowP1 << arrowP3 << arrowP2 << line().p1();
        painter->drawPolyline(linkHead);
        setLine(QLineF(arrowP3, from->pos()));
    }
    else if (linkType == Model::LinkRepr::COMPOSITION) {
        linkHead << line().p1() << arrowP1 << arrowP3 << arrowP2;
        painter->drawPolygon(linkHead);
        setLine(QLineF(arrowP3, from->pos()));
    }
    else if (linkType == Model::LinkRepr::GENERALIZATION) {
        linkHead << line().p1() << arrowP1 << arrowP2 << line().p1();
        painter->drawPolyline(linkHead);
        setLine(QLineF(arrowP4, from->pos()));
    }

    painter->drawLine(line());
}
