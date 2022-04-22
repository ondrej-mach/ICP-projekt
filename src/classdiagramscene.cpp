#include "classdiagramscene.h"
#include "linkgraphicsitem.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

ClassDiagramScene::ClassDiagramScene(QObject *parent) : QGraphicsScene(parent)
{
    //setBackgroundBrush(QColor("#FFFFFF"));

    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    ClassGraphicsItem *classSrc = new ClassGraphicsItem();
    nodes.insert(classSrc);
    this->addItem(classSrc);
    classSrc->setFlag(QGraphicsItem::ItemIsMovable);

    ClassGraphicsItem *classDst = new ClassGraphicsItem();
    nodes.insert(classDst);
    this->addItem(classDst);
    classDst->setFlag(QGraphicsItem::ItemIsMovable);

    LinkGraphicsItem *testLink = new LinkGraphicsItem(classSrc, classDst);
    nodes.insert(testLink);
    this->addItem(testLink);
    testLink->setFlag(QGraphicsItem::ItemIsMovable);
}

ClassDiagramScene::~ClassDiagramScene()
{

}
