/** @file classeditdialog.h
 *  @brief Dialog window for editing classes' methdods and attributes.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>

#include "model.h"

namespace Ui {
class ClassEditDialog;
}

class ClassEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassEditDialog(QString className, QWidget *parent = nullptr);
    ~ClassEditDialog();

private slots:
    void setDirty();
    void newAttr();
    void newMethod();
    void submit();


private:
    Ui::ClassEditDialog *ui;
    QString currentName;

    QVector<QLineEdit *> attrLineEdits;
    QVector<QLineEdit *> methodLineEdits;

    void addAttr(QString name);
    void addMethod(QString name);

    bool dirty = false;
    double coordX, coordY; // just saving for later
};

#endif // CLASSEDITDIALOG_H
