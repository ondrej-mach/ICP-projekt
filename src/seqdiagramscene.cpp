/** @file seqdiagramscene.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "seqdiagramscene.h"
#include "model.h"
#include "lifelineitem.h"
#include "interactionitem.h"
#include "activityitem.h"

#include <QGraphicsSceneMouseEvent>

SeqDiagramScene::SeqDiagramScene(Tool &tool, QObject *parent) : QGraphicsScene(parent),  tool(tool) {

}


void SeqDiagramScene::reloadData(QString name) {
    clear();

    QPen pen{Qt::black};
    QBrush redBrush{Qt::red};

    std::string sdName = name.toStdString();
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
                QString::fromStdString(ent.name)
                );
        addItem(ll);
    }

    index = 0;
    for (auto &a: actions) {
        if (a.isBinary()) {
            /*if (a.type == Model::Action::Type::RETURN)
            {swap(a.from, a.to);}*/

            InteractionItem *arrow = new InteractionItem(
                        gridToY(index),
                        gridToX(nameToGridX[a.from]),
                        gridToX(nameToGridX[a.to]),
                        QString::fromStdString(a.text),
                        a.type
                        );
            addItem(arrow);
            index++;
        }
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

double SeqDiagramScene::gridToX(int n) {
    return n * entityDistance;
}

double SeqDiagramScene::gridToY(int n) {
    return n * actionDistance;
}

int SeqDiagramScene::XtoGrid(double x) {
    return x / entityDistance;
}

int SeqDiagramScene::YtoGrid(double y) {
    return y / actionDistance;
}

void SeqDiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    QPointF point = {mouseEvent->scenePos().x(), mouseEvent->scenePos().y()};
    QList<QGraphicsItem *> itemsList = items(point);
    QPair gridPoint{XtoGrid(point.x()), YtoGrid(point.y())};
    InteractionItem *delItemInt;
    LifeLineItem *delItemLife;
    ActivityItem *delItemAct;

    switch (tool) {
        case TOOL_ENTITY:
            model.addEntity(this->diagramName.toStdString());
            emit modelChanged();
            return; // do not pass mouse events

        case TOOL_ACTIVATE:
        case TOOL_DEACTIVATE:
            //TODO
            emit modelChanged();
            break;
        case TOOL_ASYNC_MESSAGE:
        case TOOL_SYNC_MESSAGE:
        case TOOL_CREATE_MESSAGE:
        case TOOL_DESTROY_MESSAGE:
        case TOOL_RETURN_MESSAGE:
            break;
        case TOOL_DELETE:
            for (auto item: itemsList) {
                if (item->type() == InteractionItem::Type) {
                    delItemInt = qgraphicsitem_cast<InteractionItem *>(item);
                    model.removeInteraction();
                    //TODO zprovoznit delete
                    qWarning( "delete interaction");
                }
                else if (item->type() == LifeLineItem::Type) {
                    delItemLife = qgraphicsitem_cast<LifeLineItem *>(item);
                    model.removeEntity();
                    //TODO zprovoznit delete
                    qWarning( "delete lifeline");
                }
                else if (item->type() == ActivityItem::Type) {
                    delItemAct = qgraphicsitem_cast<ActivityItem *>(item);
                    model.removeActivity();
                    //TODO zprovoznit delete
                    qWarning( "delete activity");
                }
            }
            break;
        case TOOL_MOUSE:
        default:;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SeqDiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = {mouseEvent->scenePos().x(), mouseEvent->scenePos().y()};
    QList<QGraphicsItem *> itemsList = items(point);
    QPair gridPoint{XtoGrid(point.x()), YtoGrid(point.y())};
    InteractionItem *delItemInt;
    LifeLineItem *delItemLife;
    ActivityItem *delItemAct;

    switch (tool) {
        case TOOL_ENTITY:
            model.addEntity(this->diagramName.toStdString());
            emit modelChanged();
            return; // do not pass mouse events
        case TOOL_ACTIVATE:
        case TOOL_DEACTIVATE:
            //emit modelChanged();
            break;
        case TOOL_ASYNC_MESSAGE:
        case TOOL_SYNC_MESSAGE:
        case TOOL_CREATE_MESSAGE:
        case TOOL_DESTROY_MESSAGE:
        case TOOL_RETURN_MESSAGE:
            //emit modelChanged();
            break;
        case TOOL_DELETE:
            for (auto item: itemsList) {
                if (item->type() == InteractionItem::Type) {
                    delItemInt = qgraphicsitem_cast<InteractionItem *>(item);
                    model.removeInteraction();
                    //TODO zprovoznit delete
                    qWarning( "delete interaction");
                }
                else if (item->type() == LifeLineItem::Type) {
                    delItemLife = qgraphicsitem_cast<LifeLineItem *>(item);
                    model.removeEntity();
                    //TODO zprovoznit delete
                    qWarning( "delete lifeline");
                }
                else if (item->type() == ActivityItem::Type) {
                    delItemAct = qgraphicsitem_cast<ActivityItem *>(item);
                    model.removeActivity();
                    //TODO zprovoznit delete
                    qWarning( "delete activity");
                }
            }
            break;
        case TOOL_MOUSE:
        default:;
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void SeqDiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (tool) {
        case TOOL_ENTITY:
            //emit modelChanged();
            return;
        case TOOL_ACTIVATE:
        case TOOL_DEACTIVATE:
            //emit modelChanged();

        case TOOL_ASYNC_MESSAGE:
        case TOOL_SYNC_MESSAGE:
        case TOOL_CREATE_MESSAGE:
        case TOOL_DESTROY_MESSAGE:
        case TOOL_RETURN_MESSAGE:
            //emit modelChanged();

        case TOOL_DELETE:
            //emit modelChanged();

        case TOOL_MOUSE:
        default:;
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
