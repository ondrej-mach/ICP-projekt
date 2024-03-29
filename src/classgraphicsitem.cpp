/** @file classgraphicsitem.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "classgraphicsitem.h"
#include "linkgraphicsitem.h"
#include "classdiagramscene.h"

#include <QGraphicsView>
#include <QDialog>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

ClassGraphicsItem::ClassGraphicsItem(Model::ClassRepr data, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsItem(parent), myContextMenu(contextMenu)
{
    className = QString::fromStdString(data.name);
    for (auto &attr: data.attributes) {
        attributes.push_back(QString::fromStdString(attr));
    }
    for (auto &meth: data.methods) {
        methods.push_back(QString::fromStdString(meth));
    }
    setPos(data.x, data.y);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

ClassGraphicsItem::~ClassGraphicsItem() {

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
    QPair<int, int> pair = computeDimensions();
    int a = pair.first;
    int b = pair.second;
    return QRectF(-a/2, -b/2, a, b);
}

void ClassGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QBrush brushWhite(Qt::white);
    QBrush brushGray(Qt::lightGray);
    QRectF rect = boundingRect();
    painter->fillRect(rect, brushWhite);
    painter->setPen(Qt::black);
    painter->drawRect(rect);

    QPair<int, int> pair = computeDimensions();
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

QVariant ClassGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change,
                                     const QVariant &value) {
    if (change == ItemPositionChange) {
        moved = true;
    }
    return QGraphicsItem::itemChange(change, value);
}

void ClassGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    // mark myself so i can be deleted or edited
    // not really the best practice but who cares at this point
    qobject_cast<ClassDiagramScene *>(scene())->markItem(this);

    if (myContextMenu != nullptr) {
        myContextMenu->exec(event->screenPos());
    }
}

void ClassGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
    // CURSED stuff, make sure to NEVER swap these commands
    if (moved) {
        qobject_cast<ClassDiagramScene *>(scene())->itemMoved(this);
    }
}

Model::ClassRepr ClassGraphicsItem::convertToClassRepr()
{
    Model::ClassRepr classRepr{};
    classRepr.name = className.toStdString();

    classRepr.x = this->scenePos().x();
    classRepr.y = this->scenePos().y();

    for (auto &attr: attributes) {
        classRepr.attributes.push_back(attr.toStdString());
    }
    for (auto &meth: methods) {
        classRepr.methods.push_back(meth.toStdString());
    }

    return classRepr;
}

QString ClassGraphicsItem::getName() const
{
    return className;
}
