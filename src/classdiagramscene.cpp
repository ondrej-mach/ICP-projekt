#include "classdiagramscene.h"
#include "model.h"

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMap>
#include <string>

ClassDiagramScene::ClassDiagramScene(QObject *parent) : QGraphicsScene(parent) {

    ClassGraphicsItem *classSrc = new ClassGraphicsItem();
    nodes.insert("c1", classSrc);
    this->addItem(classSrc);
    classSrc->setFlag(QGraphicsItem::ItemIsMovable);

    ClassGraphicsItem *classDst = new ClassGraphicsItem();
    nodes.insert("c2", classDst);
    this->addItem(classDst);
    classDst->setFlag(QGraphicsItem::ItemIsMovable);

    LinkGraphicsItem *testLink = new LinkGraphicsItem(classSrc, classDst);
    links.insert(testLink);
    this->addItem(testLink);

}

ClassDiagramScene::~ClassDiagramScene() {

}

void ClassDiagramScene::reloadData(Model &m) {
    for (auto item: qAsConst(nodes)) {
        removeItem(item);
    }
    nodes.clear();

    for (auto item: qAsConst(links)) {
        removeItem(item);
    }
    links.clear();

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
        ClassGraphicsItem *from = nodes[QString::fromStdString(link.from)];
        ClassGraphicsItem *to = nodes[QString::fromStdString(link.to)];
        LinkGraphicsItem *lgi = new LinkGraphicsItem{from, to, link.type};
        links.insert(lgi);
        addItem(lgi);
    }
}

void ClassDiagramScene::setTool(Tool tool) {
    this->tool = tool;

}
