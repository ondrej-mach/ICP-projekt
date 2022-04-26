#include "seqdiagramscene.h"
#include "model.h"
#include "lifelineitem.h"
#include "interactionitem.h"
#include "activityitem.h"

SeqDiagramScene::SeqDiagramScene(Tool &tool, QObject *parent) : QGraphicsScene(parent), tool(tool) {

}


void SeqDiagramScene::reloadData(QString name) {
    clear();

    QBrush redBrush{Qt::red};
    QPen pen{Qt::black};

    std::vector<Model::SeqEntity> entities = model.getEntities(name.toStdString());
    std::vector<Model::Action> actions = model.getActions(name.toStdString());

    // This is inferred from model, it is not actually stored there
    struct ActiveRegion {
        std::string on;
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
        } else {
            if (a.type == Model::Action::ACTIVATE) {
                // Temporarily set from ant to to the same number
                // DEACTIVATE will find it afterwards
                activeRegions.push_back({a.from, interactionCount, interactionCount});
            } else {
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
            InteractionItem *arrow = new InteractionItem(
                        gridToY(index),
                        gridToX(nameToGridX[a.from]),
                        gridToX(nameToGridX[a.to])
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

double SeqDiagramScene::gridToX(int n){
    return n * entityDistance;
}

double SeqDiagramScene::gridToY(int n){
    return n * actionDistance;
}
