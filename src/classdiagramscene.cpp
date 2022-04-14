#include "classdiagramscene.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

ClassDiagramScene::ClassDiagramScene(QObject *parent) : QGraphicsScene(parent)
{
    //nodes.insert(new ClassNode());
    //nodes.insert(new QGraphicsRectItem);
    //item = new QGraphicsRectItem(10, 10, 90, 90);

    //setBackgroundBrush(QColor("#FFFFFF"));

    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    QGraphicsItem *rect = addRect(100, 0, 80, 100, outlinePen, blueBrush);
    rect->setFlag(QGraphicsItem::ItemIsMovable);
    nodes.insert(rect);
}

ClassDiagramScene::~ClassDiagramScene()
{

}
