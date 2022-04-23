#ifndef CLASSGRAPHICSITEM_H
#define CLASSGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QPair>
#include <QSet>
#include "model.h"

class LinkGraphicsItem;

class ClassGraphicsItem : public QGraphicsItem
{
public:
    // Qt black magic for recognizing types. do NOT touch
    enum { Type = UserType + 15 };
    int type() const override { return Type; }

    ClassGraphicsItem();
    ClassGraphicsItem(Model::ClassRepr data, QString name, QGraphicsItem *parent=nullptr);
    ~ClassGraphicsItem();

    QRectF boundingRect() const override;
    QPair<int, int> computeDimensions() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void convertToClassRepr(Model &m);

    void addLink(LinkGraphicsItem *);
    void removeLink(LinkGraphicsItem *);

private:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    int posX;
    int posY;
    QString className;
    QVector<QString> attributes;
    QVector<QString> methods;
    QSet<LinkGraphicsItem *> connectedLinks;

    static const int lineHeight = 13;
    static const int charWidth = 9;
    static const int margin = 10;

};

#endif // CLASSGRAPHICSITEM_H
