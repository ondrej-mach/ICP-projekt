#include "seqdiagramscene.h"
#include "model.h"
#include "lifelineitem.h"

SeqDiagramScene::SeqDiagramScene(Tool &tool, QObject *parent) : QGraphicsScene(parent), tool(tool) {

}


void SeqDiagramScene::reloadData(QString name) {
    clear();

    QBrush redBrush{Qt::red};
    QPen pen{Qt::black};

    std::vector<Model::SeqEntity> entities = model.getEntities(name.toStdString());
    std::vector<Model::Action> actions = model.getActions(name.toStdString());

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
            if (createdAt.find(createdObject) != createdAt.end()) {
                createdAt[createdObject] = interactionCount;
            }
        }
        // Unary actions dont occupy any space
        // they happen on the last binary interaction
        if (a.isBinary()) {
            interactionCount++;
        }
    }


    // drawing after all calculations are done
    for (auto &ent: entities) {
        LifeLineItem *ll = new LifeLineItem(
                gridToX(nameToGridX[ent.name]),
                gridToY(createdAt[ent.name]),
                gridToY(interactionCount),
                QString::fromStdString(ent.name)
                );
        addItem(ll);
    }
}

double SeqDiagramScene::gridToX(int n){
    return n * entityDistance;
}

double SeqDiagramScene::gridToY(int n){
    return n * actionDistance;
}
