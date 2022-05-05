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

InteractionItem::InteractionItem(double y, double xStart, double xEnd, QString desc, Model::Action::Type type)
    : y(y), xStart(xStart), xEnd(xEnd), desc(desc), type(type)
{
    setPos(xStart, y);
    double len = xEnd - xStart;

    setLine(QLineF(QPointF(), QPointF(len,0)));
    setZValue(-1000);
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

    bool arrowLeft = (xStart - xEnd) > 0;
    double arg = 0;
    if (arrowLeft) {
        arg = M_PI / 3;
    }
    else {
        arg = - M_PI / 3;
    }
    QPointF arrowP1 = line().p2() + arrowSize * QPointF(sin(arg), cos(arg));
    arg *= 2;
    QPointF arrowP2 = line().p2() + arrowSize * QPointF(sin(arg), cos(arg));

    interactionHead.clear();

    painter->setBrush(Qt::black);
    QPen polyPen {Qt::black, 3, Qt::SolidLine};
    QPen linePen {Qt::black, 3, Qt::SolidLine};

    painter->setPen(polyPen);

    //TODO text nad sipkou
    if (type == Model::Action::Type::SYNC) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolygon(interactionHead);
    }
    else if (type == Model::Action::Type::ASYNC) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
        linePen = {Qt::black, 3, Qt::DashLine};
    }
    else if (type == Model::Action::Type::RETURN) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
        linePen = {Qt::black, 3, Qt::DashLine};
    }
    else if (type == Model::Action::Type::CREATE) {
        P2 = P2 - QPointF(60, 0);
        arrowP1 = arrowP1 - QPointF(60, 0);
        arrowP2 = arrowP2 - QPointF(60, 0);
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
    }
    else if (type == Model::Action::Type::DESTROY) {
        interactionHead << arrowP1 << P2 << arrowP2;
        painter->drawPolyline(interactionHead);
    }

    painter->setPen(linePen);
    painter->drawLine(line());
}

QVector<double> InteractionItem::getCoords(InteractionItem *item)
{
    return QVector{item->y, item->xStart, item->xEnd};
}

