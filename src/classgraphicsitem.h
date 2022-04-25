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
    // Qt black magic for recognizing types. do NOT touch
    enum { Type = UserType + 15 };
    int type() const override { return Type; }

    ClassGraphicsItem(Model::ClassRepr data, QMenu *contextMenu=nullptr, QGraphicsItem *parent=nullptr);
    ~ClassGraphicsItem();

    QRectF boundingRect() const override;
    QPair<int, int> computeDimensions() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget) override;

    Model::ClassRepr convertToClassRepr();
    QString getName() const;

    void addLink(LinkGraphicsItem *);
    void removeLink(LinkGraphicsItem *);

private:
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
