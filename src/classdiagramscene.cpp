#include "classdiagramscene.h"
#include "model.h"

#include <QGraphicsSceneMouseEvent>
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

void ClassDiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    ClassGraphicsItem *item;
    switch (tool) {
        case TOOL_CLASS:
            item = new ClassGraphicsItem();
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            //emit itemInserted(item);
            break;

        case TOOL_AGGREGATE:
        case TOOL_ASSOCIATE:
        case TOOL_COMPOSE:
        case TOOL_GENERALIZE:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(Qt::black, 2));
            addItem(line);
            break;

        case TOOL_MOUSE:
        default:
            ;
    }
    // Do the default thing as well
    QGraphicsScene::mousePressEvent(mouseEvent);
}


void ClassDiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    bool isLineTool = (tool == TOOL_AGGREGATE)
            || (tool == TOOL_ASSOCIATE)
            || (tool == TOOL_COMPOSE)
            || (tool == TOOL_GENERALIZE);

    if (isLineTool && line != nullptr) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}


void ClassDiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    bool isLineTool = (tool == TOOL_AGGREGATE)
            || (tool == TOOL_ASSOCIATE)
            || (tool == TOOL_COMPOSE)
            || (tool == TOOL_GENERALIZE);

    if (line != nullptr && isLineTool) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == ClassGraphicsItem::Type &&
            endItems.first()->type() == ClassGraphicsItem::Type &&
            startItems.first() != endItems.first()) {
            ClassGraphicsItem *startItem = qgraphicsitem_cast<ClassGraphicsItem *>(startItems.first());
            ClassGraphicsItem *endItem = qgraphicsitem_cast<ClassGraphicsItem *>(endItems.first());
            Model::LinkRepr::Type lineType;
            switch (tool) {
                default:
                case TOOL_ASSOCIATE: lineType = Model::LinkRepr::ASSOCIATION; break;
                case TOOL_AGGREGATE: lineType = Model::LinkRepr::AGGREGATION; break;
                case TOOL_COMPOSE: lineType = Model::LinkRepr::COMPOSITION; break;
                case TOOL_GENERALIZE: lineType = Model::LinkRepr::GENERALIZATION; break;
            }
            LinkGraphicsItem *link = new LinkGraphicsItem(startItem, endItem, lineType);

            addItem(link);
            link->updatePosition();
        }
    }

    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


