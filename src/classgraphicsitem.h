#ifndef CLASSGRAPHICSITEM_H
#define CLASSGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QPair>
#include "model.h"

class ClassGraphicsItem : public QGraphicsItem
{
public:

    ClassGraphicsItem();
    ClassGraphicsItem(Model::ClassRepr data, QString name);

    QRectF boundingRect() const override;
    QPair<int, int> computeDimensions() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool Pressed;
    void convertToClassRepr(Model &m);

private:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    int posX;
    int posY;
    QString className;
    QVector<QString> attributes;
    QVector<QString> methods;

    static const int lineHeight = 13;
    static const int charWidth = 9;
    static const int margin = 10;

};

#endif // CLASSGRAPHICSITEM_H
