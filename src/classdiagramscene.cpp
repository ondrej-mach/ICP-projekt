#include "classdiagramscene.h"
#include "linkgraphicsitem.h"
#include "model.h"

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMap>
#include <string>

ClassDiagramScene::ClassDiagramScene(QObject *parent) : QGraphicsScene(parent) {


//    ClassGraphicsItem *classSrc = new ClassGraphicsItem();
//    nodes.insert("bruh", classSrc);
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

}

ClassDiagramScene::~ClassDiagramScene() {

}

void ClassDiagramScene::reloadData(Model &m) {
    for (auto &name: m.getClasses()){
        Model::ClassRepr &data = m.getClass(name);

        QString qname = QString::fromStdString(name);
        ClassGraphicsItem *cgi = new ClassGraphicsItem{data, qname};
        nodes.insert(qname, cgi);
        addItem(cgi);
        cgi->setFlag(QGraphicsItem::ItemIsMovable);
    }
    m.getLinks();
}
