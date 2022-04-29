#include "classdiagramscene.h"
#include "model.h"
#include "mainwindow.h"
#include "classeditdialog.h"

#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMap>
#include <string>

#include <QMenu>
#include <QAction>
#include "classgraphicsitem.h"

ClassDiagramScene::ClassDiagramScene(Tool &tool, QObject *parent)
    : QGraphicsScene(parent), tool(tool)
{
    editMenu = new QMenu();

    QAction *editAction = editMenu->addAction("Edit");
    connect(editAction, &QAction::triggered, this, &ClassDiagramScene::openEditDialog);
    QAction *removeAction = editMenu->addAction("Remove");
    connect(removeAction, &QAction::triggered, this, &ClassDiagramScene::itemRemoved);

}

ClassDiagramScene::~ClassDiagramScene() {
    clear(); // delete all QGraphicsItems
    delete editMenu;
}

void ClassDiagramScene::reloadData() {
    clear(); // destroy all Items, that are currently displayed
    nodes.clear();
    links.clear();

    for (auto &name: model.getClasses()) {
        Model::ClassRepr data = model.getClass(name);

        QString qname = QString::fromStdString(name);
        ClassGraphicsItem *cgi = new ClassGraphicsItem{data, editMenu};
        nodes.insert(qname, cgi);
        addItem(cgi);
    }

    for (auto &link: model.getLinks()) {
        ClassGraphicsItem *from = nodes[QString::fromStdString(link.from)];
        ClassGraphicsItem *to = nodes[QString::fromStdString(link.to)];
        LinkGraphicsItem *lgi = new LinkGraphicsItem{from, to, link.type};
        links.insert(lgi);
        addItem(lgi);
    }
}

void ClassDiagramScene::itemMoved(ClassGraphicsItem *cgi) {
    Model::ClassRepr classRepr = cgi->convertToClassRepr();
    QString currentName = nodes.key(cgi);
    model.changeClassProperties(currentName.toStdString(), classRepr);
    emit modelChanged();
}

void ClassDiagramScene::markItem(ClassGraphicsItem *cgi) {
    markedItem = cgi;
}

void ClassDiagramScene::itemRemoved() {
    QString className = nodes.key(markedItem);
    model.removeClass(className.toStdString());
    emit modelChanged();
}

void ClassDiagramScene::openEditDialog() {
    ClassEditDialog editDialog{markedItem->getName()};
    if (editDialog.exec() == QDialog::Accepted) {
        emit modelChanged();
    }
}

void ClassDiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    switch (tool) {
        case TOOL_DELETE:
            for (auto classname: model.getClasses()) {
                /*Model::ClassRepr classStruct = model.getClass(classname);
                QPair<int, int> coords = ClassGraphicsItem::computeDimensions();
                if ((mouseEvent->scenePos().x() > classStruct.x) &&
                    (mouseEvent->scenePos().x() < classStruct.x + coords.first) &&
                    (mouseEvent->scenePos().y() > classStruct.y) &&
                    (mouseEvent->scenePos().y() < classStruct.y + coords.second)) {*/
                    model.removeClass(classname);
                //}
            }
            emit modelChanged();
            return;
        case TOOL_CLASS:
            model.addClass(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
            emit modelChanged();
            return; // do not pass mouse events

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
            Model::LinkRepr link;
            link.from = startItem->getName().toStdString();
            link.to = endItem->getName().toStdString();

            switch (tool) {
                default:
                case TOOL_ASSOCIATE: link.type = Model::LinkRepr::ASSOCIATION; break;
                case TOOL_AGGREGATE: link.type = Model::LinkRepr::AGGREGATION; break;
                case TOOL_COMPOSE: link.type = Model::LinkRepr::COMPOSITION; break;
                case TOOL_GENERALIZE: link.type = Model::LinkRepr::GENERALIZATION; break;
            }
            model.addLink(link);
            emit modelChanged();
        }
    }

    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


