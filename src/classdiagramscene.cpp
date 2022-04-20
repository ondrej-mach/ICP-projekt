#include "classdiagramscene.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

ClassDiagramScene::ClassDiagramScene(QObject *parent) : QGraphicsScene(parent)
{
    //setBackgroundBrush(QColor("#FFFFFF"));

    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    ClassGraphicsItem *item = new ClassGraphicsItem();
    nodes.insert(item);
    this->addItem(item);
    item->setFlag(QGraphicsItem::ItemIsMovable);

}

ClassDiagramScene::~ClassDiagramScene()
{

}
