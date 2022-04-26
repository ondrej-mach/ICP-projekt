#include "seqdiagramscene.h"
#include <vector>
#include "model.h"

SeqDiagramScene::SeqDiagramScene(Tool &tool, QObject *parent) : QGraphicsScene(parent), tool(tool) {

}


void SeqDiagramScene::reloadData(QString name) {
    QBrush redBrush{Qt::red};
    QPen pen{Qt::black};

    std::vector<Model::SeqEntity> entities = model.getEntities(name.toStdString());
    auto actions = model.getActions(name.toStdString());

    for (auto entity: entities) {
        //auto rect = addRect(-100,-100,200,200, pen, redBrush);
        //rect->
    }
}
