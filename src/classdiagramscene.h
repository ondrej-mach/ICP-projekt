#ifndef CLASSDIAGRAMSCENE_H
#define CLASSDIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QSet>

class ClassDiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ClassDiagramScene(QObject *parent = nullptr);
    ~ClassDiagramScene();

private:
    QSet<QGraphicsItem *> nodes;
    QGraphicsItem *item;
};

#endif // CLASSDIAGRAMSCENE_H
