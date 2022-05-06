/** @file interactionitem.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "interactionitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QPen>
#include <QtMath>

InteractionItem::InteractionItem(double y, double xStart, double xEnd, QString desc, Model::Action::Type type, QString from, QString to, int index)
    : from(from), to(to), y(y), xStart(xStart), xEnd(xEnd), intType(type), desc(desc)
{
    setPos(xStart, y);
    double len = xEnd - xStart;
    this->index = index;

    setLine(QLineF(QPointF(), QPointF(len,0)));
    setZValue(-1000);
}

QPainterPath InteractionItem::shape() const {
    QPainterPath path;
    path.addPolygon(QRectF(0,-10,xEnd-xStart, 20));
    return path;
}

QRectF InteractionItem::boundingRect() const {

    return QRectF(0,-20,xEnd-xStart, 40)
        .normalized();
}

void InteractionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    qreal arrowSize = 20;

    QPointF P1 = QPointF(0, 0);
    QPointF P2 = QPointF(xEnd-xStart, 0);
    setLine(QLineF(P1, P2));

    painter->setBrush(Qt::black);
    QPen polyPen {Qt::black, 3, Qt::SolidLine};
    QPen linePen {Qt::black, 3, Qt::SolidLine};
    painter->setPen(polyPen);

    int baseLength = 150;
    int intLength =  (xEnd - xStart);
    int ticks = intLength / baseLength;
    bool arrowLeft = intLength < 0;
    if (ticks != 0) {
        if (arrowLeft) {
            // going left
            painter->drawText(-intLength/ (2 * ticks) - 40 , -8, this->desc);
        }
        else {
            // going right
            painter->drawText(intLength/ (2 * ticks) - 40, -8, this->desc);
        }
    }

    double arg = 0;
    (arrowLeft) ? arg = (M_PI / 3) : (arg = - M_PI / 3);
    QPointF arrowP1 = line().p2() + arrowSize * QPointF(sin(arg), cos(arg));
    arg *= 2;
    QPointF arrowP2 = line().p2() + arrowSize * QPointF(sin(arg), cos(arg));

    interactionHead.clear();


    //TODO text nad sipkou
    if (intType == Model::Action::Type::SYNC) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolygon(interactionHead);
    }
    else if (intType == Model::Action::Type::ASYNC) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
    }
    else if (intType == Model::Action::Type::RETURN) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
        linePen = {Qt::black, 3, Qt::DashLine};
    }
    else if (intType == Model::Action::Type::CREATE) {
        P2 = P2 - QPointF(60, 0);
        arrowP1 = arrowP1 - QPointF(60, 0);
        arrowP2 = arrowP2 - QPointF(60, 0);
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
    }
    else if (intType == Model::Action::Type::DESTROY) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
        interactionHead.clear();
        P2 = P2 + QPointF(0, 40);
        interactionHead << P2 + QPointF(20,20) << P2 + QPointF(-20,-20) << P2 << P2 + QPointF(20,-20) << P2 + QPointF(-20,20);
        painter->drawPolyline(interactionHead);
    }

    painter->setPen(linePen);
    painter->drawLine(line());
}

QVector<double> InteractionItem::getCoords(InteractionItem *item)
{
    return QVector{item->y, item->xStart, item->xEnd};
}

