#ifndef ADDTASKS_H
#define ADDTASKS_H

#include <QDialog>
#include "tomatoclock.h"

namespace Ui {
class AddTasks;
}

class AddTasks : public QDialog
{
    Q_OBJECT

public:
    explicit AddTasks(QWidget *parent = 0);
    ~AddTasks();
    QString lineStr;
    QString textStr;
    TomatoClock *little_tomatoclcok;

private slots:
    //void on_lineEdit_editingFinished();

    //void on_pushButton_clicked();

    void on_OK_clicked();

private:
    Ui::AddTasks *ui;
    void append();
};

#endif // ADDTASKS_H
