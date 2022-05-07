/** @file classgraphicsitem.h
 *  @brief Graphical item that represents class in class diagram.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef CLASSGRAPHICSITEM_H
#define CLASSGRAPHICSITEM_H

#include "model.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QPair>
#include <QSet>

#include <QDialog>


class LinkGraphicsItem;

class ClassGraphicsItem : public QGraphicsItem
{

public:
    ClassGraphicsItem(Model::ClassRepr data, QMenu *contextMenu=nullptr, QGraphicsItem *parent=nullptr);
    ~ClassGraphicsItem();

    // Qt black magic for recognizing types. do NOT touch
    enum { Type = UserType + 15 };
    int type() const override { return Type; }

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget) override;

    /** @brief Fetches name of the class.
     *  @return The name of the class.
     */
    QString getName() const;

    /** @brief Connects a link to the class.
     *  @param link Link to be connected to the class.
     *  @return Void.
     */
    void addLink(LinkGraphicsItem *link);

    /** @brief Disconnects a link from the class.
     *  @param link Link to be disconnected from the class.
     *  @return Void.
     */
    void removeLink(LinkGraphicsItem *link);

    /** @brief Converts current class to model classrepr.
     *  @return The item converted to model representation.
     */
    Model::ClassRepr convertToClassRepr();

private:

    /** @brief Computes dimensions of the item.
     *  @return Returns width and height of the item.
     */
    QPair<int, int> computeDimensions() const;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
    bool moved;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QMenu *myContextMenu;

    QString className;
    QVector<QString> attributes;
    QVector<QString> methods;
    QSet<LinkGraphicsItem *> connectedLinks;

    static const int lineHeight = 13;
    static const int charWidth = 9;
    static const int margin = 10;
};

#endif // CLASSGRAPHICSITEM_H
