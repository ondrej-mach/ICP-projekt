#include "classgraphicsitem.h"
#include "linkgraphicsitem.h"
#include <QGraphicsView>

#include <iostream>

ClassGraphicsItem::ClassGraphicsItem() {
    className = "New class";
    attributes = {"New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1","New attribute 1"};
    methods = {"New method 1","New method 1","New method 1","New method 1","New method 1","New method 1"};
}

ClassGraphicsItem::ClassGraphicsItem(Model::ClassRepr data, QString name, QGraphicsItem *parent)
    : QGraphicsItem(parent)
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
    return QRectF(-a/2, -b/2, a, b);
}

void ClassGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QBrush brushWhite(Qt::white);
    QBrush brushGray(Qt::lightGray);
    QRectF rect = boundingRect();
    painter->fillRect(rect, brushWhite);
    painter->setPen(Qt::black);
    painter->drawRect(rect);

    QPair pair = computeDimensions();
    painter->translate(-pair.first/2, -pair.second/2);

    int len = pair.first;
    int numAttr = attributes.size();
    int numMeth = methods.size();

    QRectF recClassName = QRectF(0, 0, len, lineHeight + margin * 3/2);
    painter->fillRect(recClassName, brushGray);
    painter->drawText(margin, lineHeight + margin / 2, className);
    painter->drawLine(0, lineHeight + margin * 3/2, len, lineHeight + margin * 3/2);
    painter->drawLine(0, (lineHeight + margin) * (numAttr + 1) + margin, len, (lineHeight + margin) * (numAttr + 1) + margin);

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

QVariant ClassGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange) {
        for (auto link: qAsConst(connectedLinks)) {
            link->updatePosition();
        }
    }

    return value;
}

void ClassGraphicsItem::convertToClassRepr(Model &m)
{
    Model::ClassRepr classRepr;
    classRepr.name = className.toUtf8().constData();
    classRepr.x = this->x();
    classRepr.y = this->y();
    for (auto &attr: attributes) {
        classRepr.attributes.push_back(attr.toUtf8().constData());
    }
    for (auto &meth: methods) {
        classRepr.methods.push_back(meth.toUtf8().constData());
    }
    m.changeClassProperties(className.toUtf8().constData(), classRepr);
}
