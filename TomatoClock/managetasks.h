#ifndef MANAGETASKS_H
#define MANAGETASKS_H

#include <QDialog>
#include <QStandardItemModel>
#include <QString>

namespace Ui {
class managetasks;
}

class managetasks : public QDialog
{
    Q_OBJECT

public:
    explicit managetasks(QWidget *parent = 0);
    ~managetasks();
    void myShow();
    QStandardItemModel *model;

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::managetasks *ui;
    QString manDeletes;
};

#endif // MANAGETASKS_H
