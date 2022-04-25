#ifndef CLASSEDITDIALOG_H
#define CLASSEDITDIALOG_H

#include <QDialog>

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

private:
    Ui::ClassEditDialog *ui;
    QString currentName;
};

#endif // CLASSEDITDIALOG_H
