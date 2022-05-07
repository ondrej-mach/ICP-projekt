/** @file seqdiagramscene.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "seqdiagramscene.h"
#include "model.h"
#include "interactionitem.h"
#include "activityitem.h"
#include "lifelineitem.h"
#include "entityeditdialog.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMenu>

SeqDiagramScene::SeqDiagramScene(Tool &tool, QObject *parent) : QGraphicsScene(parent), tool(tool) {
    entityEditMenu = new QMenu();

    QAction *editAction = entityEditMenu->addAction("Rename");
    connect(editAction, &QAction::triggered, this, &SeqDiagramScene::openEditDialog);
}

SeqDiagramScene::~SeqDiagramScene() {
    clear();
    delete entityEditMenu;
}


void SeqDiagramScene::markItem(LifeLineItem *lli) {
    markedItem = lli;
}

void SeqDiagramScene::openEditDialog() {
    EntityEditDialog editDialog{markedItem->getName(), getName(this)};
    if (editDialog.exec() == QDialog::Accepted) {
        emit modelChanged();
    }
}

void SeqDiagramScene::reloadData(QString name) {
    clear();
    this->entities.clear();
    this->actions.clear();

    QPen pen{Qt::black};
    QBrush redBrush{Qt::red};

    std::string sdName = name.toStdString();
    diagramName = name;
    std::vector<Model::SeqEntity> entities = model.getEntities(sdName);
    std::vector<Model::Action> actions = model.getActions(sdName);

    // This is inferred from model, it is not actually stored there
    struct ActiveRegion {
        std::string on; //entity name
        int from;
        int to;
    };
    std::vector<ActiveRegion> activeRegions;

    std::map<std::string, int> nameToGridX;
    std::map<std::string, int> createdAt;

    // first calculate everything

    int index = 0;
    for (Model::SeqEntity &ent: entities) {
        nameToGridX[ent.name] = index;

        index++;
    }

    int interactionCount = 0; // first action is placed at grid 0 (in Y direction)
    for (Model::Action &a: actions) {
        // If this is special create operator, it will shift
        // the rectangle with class name down
        if (a.type == Model::Action::CREATE) {
            auto &createdObject = a.to;

            // if the object has no entry in map
            if (createdAt.find(createdObject) == createdAt.end()) {
                createdAt[createdObject] = interactionCount;
            }
        }

        // Unary actions dont occupy any space
        // they happen on the last binary interaction
        if (a.isBinary()) {
            interactionCount++;
        }
        else {
            if (a.type == Model::Action::ACTIVATE) {
                // Temporarily set from ant to the same number
                // DEACTIVATE will find it afterwards
                activeRegions.push_back({a.from, interactionCount, interactionCount});
            }
            else {
                // Find the right activate action to complete the structure
                for (auto &ar: activeRegions) {
                    if ((a.from == ar.on) && (ar.from == ar.to)) {
                        ar.to = interactionCount;
                        break;
                    }
                }
            }
        }
    }

    // drawing after all calculations are done
    for (auto &ent: entities) {
        // if the object was not created with an action
        // Then it started at -1 on grid Y axis
        if (createdAt.find(ent.name) == createdAt.end()) {
            createdAt[ent.name] = -1;
        }

        LifeLineItem *ll = new LifeLineItem(
                gridToX(nameToGridX[ent.name]),
                gridToY(createdAt[ent.name]),
                gridToY(interactionCount),
                QString::fromStdString(ent.name),
                false,
                entityEditMenu
                );
        std::vector<std::string> classes = model.getClasses();
        if (std::find(classes.begin(), classes.end(), ent.name) != classes.end()) {
            ll->inClassDiag = true;
        }
        this->entities.insert(QString::fromStdString(ent.name), ll);
        addItem(ll);
    }

    index = 0;
    int binaryIndex = 0;
    for (auto &a: actions) {
        if (a.isBinary()) {

            InteractionItem *arrow = new InteractionItem(
                        gridToY(binaryIndex),
                        gridToX(nameToGridX[a.from]),
                        gridToX(nameToGridX[a.to]),
                        QString::fromStdString(a.text),
                        a.type,
                        a.from.c_str(),
                        a.to.c_str(),
                        index
                        );
            this->actions.append(arrow);
            addItem(arrow);
            binaryIndex++;
        }
        index++;
    }

    for (auto &ar: activeRegions) {
        // This item has not been deactivated
        // so were gonna display activation to the end
        if (ar.from == ar.to) {
            ar.to = interactionCount;
        }
        ActivityItem *ai = new ActivityItem(
                   gridToX(nameToGridX[ar.on]),
                   gridToY(ar.from),
                   gridToY(ar.to)
                   );
        addItem(ai);
   }
}

QString SeqDiagramScene::getName(SeqDiagramScene *scene)
{
    return scene->diagramName;
}

double SeqDiagramScene::gridToX(int n) {
    return n * entityDistance;
}

double SeqDiagramScene::gridToY(int n) {
    return n * actionDistance;
}

void SeqDiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    QPointF point = {mouseEvent->scenePos().x(), mouseEvent->scenePos().y()};
    QList<QGraphicsItem *> itemsList = items(point);
    LifeLineItem *delEntity;
    QVector<double> coords;
    InteractionItem *delItemInteraction;
    //ActivityItem *delItemAct;

    switch (tool) {
        case TOOL_ENTITY:
            model.addEntity(this->diagramName.toStdString());
            emit modelChanged();
            return;
        case TOOL_DELETE:
            for (auto item: itemsList) {
                if (item->type() == LifeLineItem::Type) {
                    delEntity = qgraphicsitem_cast<LifeLineItem *>(item);
                    QString entityName = delEntity->getName();
                    model.removeEntity(getName(this), entityName);
                    emit modelChanged();
                }
                else if (item->type() == InteractionItem::Type) {
                    delItemInteraction = qgraphicsitem_cast<InteractionItem *>(item);
                    model.removeInteraction(getName(this), delItemInteraction->index);
                    emit modelChanged();
                }
                else if (item->type() == ActivityItem::Type) {
                    //delItemAct = qgraphicsitem_cast<ActivityItem *>(item);
                    // TODO fce, co neni v modelu a co rusi aktivitu
                    emit modelChanged();
                }
            }
            break;
        case TOOL_ASYNC_MESSAGE:
        case TOOL_SYNC_MESSAGE:
        case TOOL_CREATE_MESSAGE:
        case TOOL_DESTROY_MESSAGE:
        case TOOL_RETURN_MESSAGE:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            line->setPen(QPen(Qt::black, 2));
            addItem(line);
            break;
        case TOOL_ACTIVATE:
        case TOOL_DEACTIVATE:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            line->setPen(QPen(Qt::black, 2));
            addItem(line);
            break;
        case TOOL_MOUSE:
        default:;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SeqDiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (tool) {

        case TOOL_ASYNC_MESSAGE:
        case TOOL_SYNC_MESSAGE:
        case TOOL_CREATE_MESSAGE:
        case TOOL_DESTROY_MESSAGE:
        case TOOL_RETURN_MESSAGE:
            if (line != nullptr) {
                QLineF newLine(line->line().p1(),
                    QPointF(mouseEvent->scenePos().x(), line->line().p1().y()));
                line->setLine(newLine);
            } else {
                QGraphicsScene::mouseMoveEvent(mouseEvent);
            }
            break;
        case TOOL_ACTIVATE:
            if (line != nullptr) {
                QLineF newLine(line->line().p1(),
                    QPointF(line->line().p1().x(), mouseEvent->scenePos().y()));
                line->setLine(newLine);
            } else {
                QGraphicsScene::mouseMoveEvent(mouseEvent);
            }
            break;
        case TOOL_DEACTIVATE:
        case TOOL_DELETE:
        case TOOL_MOUSE:
        default:;
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void SeqDiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = {mouseEvent->scenePos().x(), mouseEvent->scenePos().y()};
    QList<QGraphicsItem *> itemsList = items(point);
    QVector<double> coords;
    QString from, to, on;
    double entityX;
    Model::Action::Type actionType;

    switch (tool) {
        case TOOL_ACTIVATE:
        case TOOL_DEACTIVATE:
            actionType = Model::Action::Type::ACTIVATE;
            for (auto entity: this->entities) {
                coords = entity->getCoords(entity);
                entityX = coords.first();
            }
            removeItem(line);
            reloadData(this->getName(this));
            delete line;
            break;
        case TOOL_ASYNC_MESSAGE:
        case TOOL_SYNC_MESSAGE:
        case TOOL_CREATE_MESSAGE:
        case TOOL_DESTROY_MESSAGE:
        case TOOL_RETURN_MESSAGE:
            if (line != nullptr) {
                int startPointX = line->line().p1().x();
                int endPointX = line->line().p2().x();
                int distance = startPointX - endPointX;
                switch (tool) {
                    default:
                    case TOOL_ASYNC_MESSAGE: actionType = Model::Action::Type::ASYNC; break;
                    case TOOL_SYNC_MESSAGE: actionType = Model::Action::Type::SYNC; break;
                    case TOOL_CREATE_MESSAGE: actionType = Model::Action::Type::CREATE; break;
                    case TOOL_DESTROY_MESSAGE: actionType = Model::Action::Type::DESTROY; break;
                    case TOOL_RETURN_MESSAGE: actionType = Model::Action::Type::RETURN; break;
                }
                removeItem(line);
                delete line;

                // Check for correct length of line
                if (((distance > 0) && (distance % 150 < 130) && (distance % 150 > 20)) ||
                 ((distance <= 0) && (distance % 150 > -130) && (distance % 150 < -20))) {
                    return;
                }

                // Select correct entities
                for (auto &entity: this->entities) {
                    coords = entity->getCoords(entity);
                    entityX = coords.first();
                    if ((entityX < (startPointX + 20)) && (entityX > (startPointX - 20))) {
                        from = entity->getName();
                    }
                    if ((entityX < (endPointX + 20)) && (entityX > (endPointX - 20))) {
                        to = entity->getName();
                    }
                }

                // Add if between two different entities
                if (from != to) {
                    model.addInteraction(getName(this), from, to, actionType);
                    emit modelChanged();
                }
            }
            return;
        case TOOL_DELETE:
        case TOOL_MOUSE:
        default:;
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

