#include "classgraphicsitem.h"
#include <iostream>

ClassGraphicsItem::ClassGraphicsItem()
{
    Pressed = false;
    className = "New class";
    attributes = {"New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1"};
    methods = {"New method 1","New method 1","New method 1","New method 1","New method 1","New method 1"};
}

QPair<int, int> ClassGraphicsItem::computeDimensions() const
{
    int charLen = className.length();
    for (auto attr : attributes) {
        charLen = std::max(attr.length(), charLen);
    }
    for (auto meth : methods) {
        charLen = std::max(meth.length(), charLen);
    }
    int numAttr = attributes.size();
    int numMeth = methods.size();

    int len = charLen * charWidth;
    int height = (lineHeight + margin) * (numAttr + numMeth + 1) + margin;

    return {len, height};
}


QRectF ClassGraphicsItem::boundingRect() const
{
    QPair pair = computeDimensions();
    int a = pair.first;
    int b = pair.second;
    return QRectF(0, 0, a, b);
}

void ClassGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QBrush brushWhite(Qt::white);
    QBrush brushGray(Qt::lightGray);
    QRectF rect = boundingRect();

    painter->fillRect(rect, brushWhite);

    QPair pair = computeDimensions();

    int len = pair.first;
    int numAttr = attributes.size();
    int numMeth = methods.size();

    QRectF recClassName = QRectF(0, 0, len, lineHeight + margin * 3/2);
    painter->fillRect(recClassName, brushGray);
    painter->setPen(Qt::black);
    painter->drawText(margin, lineHeight + margin / 2, className);
    painter->drawLine(0, lineHeight + margin * 3/2, len, lineHeight + margin * 3/2);
    painter->drawLine(0, (lineHeight + margin) * (numAttr + 1) + margin, len, (lineHeight + margin) * (numAttr + 1) + margin);
    painter->drawRect(rect);

    for (int i = 0; i < numAttr; i++) {
        painter->drawText(margin, (lineHeight + margin) * (i + 2), attributes[i]);
    }
    for (int i = 0; i < numMeth; i++) {
        painter->drawText(margin, (lineHeight + margin) * (numAttr + i + 2) + margin/2 , methods[i]);
    }
}

void ClassGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void ClassGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
