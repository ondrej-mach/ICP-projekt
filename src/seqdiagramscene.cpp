#include "seqdiagramscene.h"


SeqDiagramScene::SeqDiagramScene(Tool &tool, QObject *parent) : QGraphicsScene(parent), tool(tool) {

}


void SeqDiagramScene::reloadData(QString name) {
    model;
    QBrush redBrush{Qt::red};
    QPen pen{Qt::black};

    addRect(-100,-100,200,200, pen, redBrush);
}
