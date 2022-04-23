#include "classdiagramscene.h"
#include "model.h"

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMap>
#include <string>

ClassDiagramScene::ClassDiagramScene(QObject *parent) : QGraphicsScene(parent) {

    ClassGraphicsItem *classSrc = new ClassGraphicsItem();
    nodes.insert("bruh", classSrc);
    this->addItem(classSrc);
    classSrc->setFlag(QGraphicsItem::ItemIsMovable);

    ClassGraphicsItem *classDst = new ClassGraphicsItem();
    nodes.insert("bruh", classDst);
    this->addItem(classDst);
    classDst->setFlag(QGraphicsItem::ItemIsMovable);

    LinkGraphicsItem *testLink = new LinkGraphicsItem(classSrc, classDst);
    links.insert(testLink);
    this->addItem(testLink);
    testLink->setFlag(QGraphicsItem::ItemIsMovable);

}

ClassDiagramScene::~ClassDiagramScene() {

}

void ClassDiagramScene::reloadData(Model &m) {
    return;
    for (auto &item: nodes) {
        removeItem(item);
    }
    //nodes.clear();

    for (auto &item: links) {
        removeItem(item);
    }
    //links.clear();

    for (auto &name: m.getClasses()) {
        Model::ClassRepr &data = m.getClass(name);

        QString qname = QString::fromStdString(name);
        ClassGraphicsItem *cgi = new ClassGraphicsItem{data, qname};
        nodes.insert(qname, cgi);
        addItem(cgi);

        cgi->setFlag(QGraphicsItem::ItemIsMovable);
        cgi->setX(data.x);
        cgi->setY(data.y);
    }

    for (auto &link: m.getLinks()) {
        //TODO pouzit spravny konstruktor
        //LinkGraphicsItem *lgi = new LinkGraphicsItem{link};
        //links.insert(lgi);
        //addItem(lgi);
    }
}
