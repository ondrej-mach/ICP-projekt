/** @file entityeditdialog.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "entityeditdialog.h"
#include "ui_entityeditdialog.h"
#include <QLineEdit>
#include <QMessageBox>

EntityEditDialog::EntityEditDialog(QString entityName, QString sdName, QWidget *parent) :
    QDialog(parent), ui(new Ui::EntityEditDialog)
{
    ui->setupUi(this);
    setModal(true);

    this->currentName = entityName;
    this->sdName = sdName;

    ui->nameEdit->setText(entityName);
    connect(ui->nameEdit, &QLineEdit::textChanged, this, &EntityEditDialog::setDirty);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EntityEditDialog::submit);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EntityEditDialog::reject);
}

EntityEditDialog::~EntityEditDialog() {
    delete ui;
}

void EntityEditDialog::setDirty() {
    dirty = true;
}

void EntityEditDialog::submit()
{
    // Reject if not changed
    if (!dirty) {
        reject();
        return;
    }

    QString newName = ui->nameEdit->text();

    model.changeEntityProperties(sdName.toStdString(), currentName.toStdString(), newName.toStdString());
    accept();
}
