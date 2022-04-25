#include "classeditdialog.h"
#include "ui_classeditdialog.h"

ClassEditDialog::ClassEditDialog(QString className, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassEditDialog)
{
    ui->setupUi(this);
    setModal(true);

    currentName = className;
    Model::ClassRepr cls = model.getClass(currentName.toStdString());
    ui->nameEdit->setText(currentName);
}

ClassEditDialog::~ClassEditDialog()
{
    delete ui;
}
