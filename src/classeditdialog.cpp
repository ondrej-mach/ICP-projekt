/** @file classeditdialog.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "classeditdialog.h"
#include "ui_classeditdialog.h"
#include <QLineEdit>
#include <QMessageBox>

ClassEditDialog::ClassEditDialog(QString className, QWidget *parent) :
    QDialog(parent), ui(new Ui::ClassEditDialog)
{
    ui->setupUi(this);
    setModal(true);

    currentName = className;
    Model::ClassRepr cls = model.getClass(currentName.toStdString());
    coordX = cls.x;
    coordY = cls.y;

    ui->nameEdit->setText(currentName);
    connect(ui->nameEdit, &QLineEdit::textChanged, this, &ClassEditDialog::setDirty);

    for (auto &attr: cls.attributes) {
        addAttr(QString::fromStdString(attr));
    }

    for (auto &method: cls.methods) {
        addMethod(QString::fromStdString(method));
    }

    connect(ui->newAttrButton, &QPushButton::clicked, this, &ClassEditDialog::newAttr);
    connect(ui->newMethodButton, &QPushButton::clicked, this, &ClassEditDialog::newMethod);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ClassEditDialog::submit);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &ClassEditDialog::reject);
}

ClassEditDialog::~ClassEditDialog() {
    delete ui;
}

void ClassEditDialog::addAttr(QString name) {
    QLineEdit *lineEdit = new QLineEdit(this);
    attrLineEdits.append(lineEdit);
    connect(lineEdit, &QLineEdit::textChanged, this, &ClassEditDialog::setDirty);
    lineEdit->setText(name);
    ui->attributesLayout->addWidget(lineEdit);
}

void ClassEditDialog::addMethod(QString name){
    QLineEdit *lineEdit = new QLineEdit(this);
    methodLineEdits.append(lineEdit);
    connect(lineEdit, &QLineEdit::textChanged, this, &ClassEditDialog::setDirty);
    lineEdit->setText(name);
    ui->methodsLayout->addWidget(lineEdit);
}

void ClassEditDialog::setDirty() {
    dirty = true;
}

void ClassEditDialog::newAttr()
{
    addAttr("");
}

void ClassEditDialog::newMethod()
{
    addMethod("");
}

void ClassEditDialog::submit()
{
    if (!dirty) {
        reject();
        return;
    }

    Model::ClassRepr cls;
    cls.name = ui->nameEdit->text().toStdString();

    if ((currentName.toStdString() != cls.name) && model.classExists(cls.name)) {
        QMessageBox box;
        box.setText("Class with this name already exists");
        box.exec();
        return;
    }

    for (auto &le: attrLineEdits) {
        QString name = le->text();
        if (!name.isEmpty()) {
            cls.attributes.push_back(name.toStdString());
        }
    }

    for (auto &le: methodLineEdits) {
        QString name = le->text();
        if (!name.isEmpty()) {
            cls.methods.push_back(name.toStdString());
        }
    }

    cls.x = coordX;
    cls.y = coordY;

    model.changeClassProperties(currentName.toStdString(), cls);
    accept();
}

