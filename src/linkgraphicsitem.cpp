
#include "linkgraphicsitem.h"

#include <QPainter>
#include <QPen>
#include <QtMath>

LinkGraphicsItem::LinkGraphicsItem(ClassGraphicsItem *from, ClassGraphicsItem *to, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), from(from), to(to) {

    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    to->addLink(this);
    from->addLink(this);
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
        QLineF::IntersectionType intersectionType =
            polyLine.intersects(centerLine, &intersectPoint);
        if (intersectionType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, from->pos()));

    double angle = std::atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);

    linkHead.clear();
    linkHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(linkHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}

void LinkGraphicsItem::convertToLinkRepr(Model &m)
{
    Model::LinkRepr linkRepr;
    //linkRepr.from = from;
    //linkRepr.to = to;

    //m.changeClassProperties(, linkRepr);
}



