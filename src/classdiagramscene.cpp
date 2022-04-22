#include "classdiagramscene.h"
#include "linkgraphicsitem.h"
#include "model.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMap>

ClassDiagramScene::ClassDiagramScene(QObject *parent, Model *model) : QGraphicsScene(parent)
{
    this->model = model;

//    ClassGraphicsItem *classSrc = new ClassGraphicsItem();
//    nodes.insert(classSrc);
//    this->addItem(classSrc);
//    classSrc->setFlag(QGraphicsItem::ItemIsMovable);
//
//    ClassGraphicsItem *classDst = new ClassGraphicsItem();
//    nodes.insert(classDst);
//    this->addItem(classDst);
//    classDst->setFlag(QGraphicsItem::ItemIsMovable);
//
//    LinkGraphicsItem *testLink = new LinkGraphicsItem(classSrc, classDst);
//    nodes.insert(testLink);
//    this->addItem(testLink);
//    testLink->setFlag(QGraphicsItem::ItemIsMovable);
    reloadData(this->model);
}

ClassDiagramScene::~ClassDiagramScene()
{

}

void ClassDiagramScene::reloadData(Model *m)
{
    for (auto name: m->getClasses()){
        Model::ClassRepr data = m->getClass(name);
        ClassGraphicsItem(data, QString::fromStdString(name));
    }
    m->getLinks();
}
