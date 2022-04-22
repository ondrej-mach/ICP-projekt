#include "classgraphicsitem.h"
#include "linkgraphicsitem.h"

#include <iostream>

ClassGraphicsItem::ClassGraphicsItem() {
    className = "New class";
    attributes = {"New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1"};
    methods = {"New method 1","New method 1","New method 1","New method 1","New method 1","New method 1"};
}

ClassGraphicsItem::ClassGraphicsItem(Model::ClassRepr data, QString name)
{
    className = name;
    for (auto &attr: data.attributes) {
        attributes.push_back(QString::fromStdString(attr));
    }
    for (auto &meth: data.methods) {
        methods.push_back(QString::fromStdString(meth));
    }
}

ClassGraphicsItem::~ClassGraphicsItem() {
    for (auto link: connectedLinks) {
        //delete link; // THIS MIGHT BE SHOOT IN THE FOOT
    }
}

QPair<int, int> ClassGraphicsItem::computeDimensions() const
{
    int charLen = className.length();
    for (auto &attr : attributes) {
        charLen = std::max(attr.length(), charLen);
    }
    for (auto &meth : methods) {
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

void ClassGraphicsItem::addLink(LinkGraphicsItem *link) {
    connectedLinks.insert(link);
}

void ClassGraphicsItem::removeLink(LinkGraphicsItem *link) {
    connectedLinks.remove(link);
}

void ClassGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    this->QGraphicsItem::mouseMoveEvent(event);

    for (auto link: connectedLinks) {
        link->update();
    }
}

