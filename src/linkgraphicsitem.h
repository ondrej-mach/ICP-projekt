#ifndef LINKGRAPHICSITEM_H
#define LINKGRAPHICSITEM_H

#include <QGraphicsItem>
#include "classgraphicsitem.h"

class LinkGraphicsItem : public QGraphicsItem
{
public:
    LinkGraphicsItem(QGraphicsItem *from, QGraphicsItem *to);

private:
    QGraphicsItem *from;
    QGraphicsItem *to;
};

#endif // LINKGRAPHICSITEM_H
