/** @file entityeditdialog.h
 *  @brief Dialog window for editing entities' name.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef ENTITYEDITDIALOG_H
#define ENTITYEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>

#include "model.h"

namespace Ui {
class EntityEditDialog;
}

class EntityEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntityEditDialog(QString entityName, QString sdName, QWidget *parent = nullptr);
    ~EntityEditDialog();

private slots:
    void submit();
    void setDirty();

private:
    Ui::EntityEditDialog *ui;
    QString currentName;
    QString sdName;

    bool dirty = false;
};

#endif // ENTITYEDITDIALOG_H
