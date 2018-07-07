#include "addtasks.h"
#include "ui_addtasks.h"
#include <QTextStream>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include  "tomatoclock.h"


AddTasks::AddTasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTasks)
{
    ui->setupUi(this);

}

AddTasks::~AddTasks()
{
    delete ui;
}

void AddTasks::append()
{

    QSqlQuery query;
    query.exec("select *from information");
    QString savesql = QString("insert into information");
    savesql += QString(" values(null,'%1','%2',0)").arg(ui->tasksname->text())
                .arg(ui->tasksdetail->toPlainText());
    bool ok = query.exec(savesql);
    if(ok){
          QMessageBox::about(NULL, "Save", "save new database success");
          }
    else{
         QMessageBox::about(NULL, "Save", "error save new database");
        }

}
/*void AddTasks::on_lineEdit_editingFinished()
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    lineStr = ui->tasksname->text();
}

void AddTasks::on_pushButton_clicked()
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    textStr = ui->tasksdetail->toPlainText();
    //append();
}*/

void AddTasks::on_OK_clicked()
{
    //TomatoClock *tomato_clock =new TomatoClock;
    //tomato_clock->tasks_Show();
    qDebug()<<"tasks_show";
    append();
    this->close();
}
