#include "seqdiagramscene.h"


SeqDiagramScene::SeqDiagramScene(QObject *parent) : QGraphicsScene(parent) {

}

void SeqDiagramScene::setTool(Tool tool) {
    this->tool = tool;
}

void SeqDiagramScene::reloadData() {
    model;
}
