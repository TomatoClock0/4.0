#include "managetasks.h"
#include "ui_managetasks.h"
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>

managetasks::managetasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managetasks)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet(tr("background-image: url(images/deletes.jpg);"));
    ui->pushButton_2->setStyleSheet(tr("background-image: url(images/clears.jpg);"));
    myShow();
}


managetasks::~managetasks()
{
    delete ui;
}

void managetasks::on_pushButton_clicked()
{
    qDebug()<<manDeletes;
    QSqlQuery query;
    QString deletesql = QString("delete from information where line='");
    deletesql += manDeletes;
    deletesql += QString("'");
    bool success = query.exec(deletesql);
    if(success)
    {
        QMessageBox::about(NULL, "Reset", "clear success");
       // tasks_Show();
    }
    else {
        QMessageBox::about(NULL, "Reset", "error");
    }
}
void managetasks::myShow()
{
    model=new QStandardItemModel();
    model->setColumnCount(1);
    model->setHeaderData(0,Qt::Horizontal,QStringLiteral("TASKS"));
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->setColumnWidth(0,800);
    QSqlQuery query;
    bool success = query.exec("select *from information");
    if (success)
    {
        int i=0;
        while(query.next())
        {
            if(query.value(3).toString() == '1')
            {
              model->setItem(i,new QStandardItem(query.value(1).toString()));
              i++;
            }
        }
    }
}

void managetasks::on_tableView_clicked(const QModelIndex &index)
{
    manDeletes = index.data().toString();
}

void managetasks::on_pushButton_2_clicked()
{
    QSqlQuery query;
    QString deletesql = QString("delete from information where conditions=1");
    bool success = query.exec(deletesql);
    if(success)
    {
        QMessageBox::about(NULL, "Reset", "Reset database success");
    }
    else {
        QMessageBox::about(NULL, "Reset", "error");
    }
}
