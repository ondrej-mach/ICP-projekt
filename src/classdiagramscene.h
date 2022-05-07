/** @file classdiagramscene.h
 *  @brief Graphical scene for drawing and editing the class diagrams.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef CLASSDIAGRAMSCENE_H
#define CLASSDIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QSet>
#include <QtCore>
#include <QtGui>
#include "classgraphicsitem.h"
#include "linkgraphicsitem.h"
#include "model.h"
#include "tool.h"

class ClassDiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ClassDiagramScene(Tool &tool, QObject *parent = nullptr);
    ~ClassDiagramScene();

    /** @brief Reloads data from model, puts them onto scene.
     *  @return Void.
     */
    void reloadData();

    /** @brief Checks, whether an item has been moved.
     *  @param cgi The item to be checked.
     *  @return Void.
     */
    void itemMoved(ClassGraphicsItem *cgi);

    /** @brief Marks item.
     *  @param cgi The item to be marked.
     *  @return Void.
     */
    void markItem(ClassGraphicsItem *cgi);

public slots:
    void itemRemoved();
    void openEditDialog();

signals:
    void modelChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    QMap<QString, ClassGraphicsItem *> nodes;
    QSet<LinkGraphicsItem *> links;
    Tool &tool;

    // temporary line when connecting classes
    QGraphicsLineItem *line = nullptr;

    QMenu *editMenu; // edit menu for classes
    ClassGraphicsItem *markedItem;
};

#endif // CLASSDIAGRAMSCENE_H
