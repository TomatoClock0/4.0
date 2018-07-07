#include "tomatoclock.h"
#include "ui_tomatoclock.h"
#include "addtasks.h"
#include "managetasks.h"
#include "qstring.h"
#include <QTimer>
#include <QMessageBox>
#include <QtCore>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include <QModelIndex>

static int workTime = 3;
static int relaxTime = 3;
static int remainTime = 0;

int clock_status = 0;//0--not working
                     //1--working
                     //2--relaxing
                     //3--stopping


TomatoClock::TomatoClock(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::TomatoClock)
{
    ui->setupUi(this);
    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(myslot1()));
    timer2 = timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(myslot2()));
    timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(myslot3()));

    ui->Start->setStyleSheet(tr("background-image: url(images/plays.jpg);"));
    ui->Stop->setStyleSheet(tr("background-image: url(images/stops.jpg);"));
    ui->Finish->setStyleSheet(tr("background-image: url(images/oks.jpg);"));
    ui->Delete->setStyleSheet(tr("background-image: url(images/deletes.jpg);"));
    ui->Clear->setStyleSheet(tr("background-image: url(images/clears.jpg);"));
    ui->Add->setStyleSheet(tr("background-image: url(images/add.jpg);"));
    ui->Done->setStyleSheet(tr("background-image: url(images/oks.jpg);"));
    ui->Manage->setStyleSheet(tr("background-image: url(images/manages.jpg);"));
    QFont ft;
    ft.setPointSize(12);
    ui->label->setFont(ft);
    ui->label_2->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pa);
    ui->label_2->setPalette(pa);
    QPalette palette;
    palette.setBrush(QPalette::Text,Qt::red);
    ui->addlabel->setPalette(palette);
    ui->tasksdetail->setFont(QFont("Timers",20,QFont::Bold));
    tasks_Show();

}

TomatoClock::~TomatoClock()
{
    delete ui;
}

//add tasks
void TomatoClock::on_Add_clicked()
{
    AddTasks *addtasks=new AddTasks;
    addtasks->show();
}

//manage tasks
void TomatoClock::on_Manage_clicked()
{
    managetasks *manage = new managetasks;
    manage->show();
}

//the work/relax time has been setted already
void TomatoClock::on_Done_clicked()
{
    const int w = ui->work_time->text().toInt();
    const int r=ui->relax_time->text().toInt();
    workTime = w ;
    relaxTime = r ;
    ui->clock->setText(QString::number(w));
    ui->clock1->setText(QString::number(r));
}


//**************clock**************
//show the warning
void TomatoClock::myslot1()
{
    QMessageBox::warning(this,"timer1",QObject::trUtf8("relax!"));
    timer1->stop();
    timer2->start(relaxTime*1000);
}
void TomatoClock::myslot2()
{
    QMessageBox::warning(this,"timer2",QObject::trUtf8("worK!"));
    timer2->stop();
    timer1->start(workTime*1000);
}
void TomatoClock::myslot3()
{
    clock_status = 1;
    QMessageBox::warning(this, "timer3", QObject::trUtf8("work!"));
    timer3->stop();
    timer2->start(relaxTime*1000);
}


//start to time
void TomatoClock::on_Start_clicked()
{
    clock_status = 1;
    timer1->start(workTime*1000);
}

void TomatoClock::on_Stop_clicked()
{
    if(clock_status==3){
        timer3->start(remainTime);
    }
    if(clock_status == 1&&clock_status != 3){
        remainTime=timer1->remainingTime();
        timer1->stop();
        clock_status=3;
    }
}
void TomatoClock::on_Finish_clicked()
{
    clock_status = 0;
    timer1->stop();
    timer2->stop();
}


void TomatoClock::tasks_Show()
{
    QSqlQuery query;
    QStandardItemModel *model1=new QStandardItemModel();
    model1->setColumnCount(1);
    model1->setHeaderData(0,Qt::Horizontal,QStringLiteral("UNIFINISHED TASKS"));
    ui->addlabel->setModel(model1);
    ui->addlabel->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->addlabel->setColumnWidth(0,800);
    QStandardItemModel *model2=new QStandardItemModel();
    model2->setColumnCount(1);
    model2->setHeaderData(0,Qt::Horizontal,QStringLiteral("FINISHED　TASKS"));
    ui->completedlabel->setModel(model2);
    ui->completedlabel->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->completedlabel->setColumnWidth(0,800);

    bool success = query.exec("select *from information");
    if (success)
    {
        int i=0;
        int j=0;
        while(query.next())
        {
            if(query.value(3).toString() == '0')
            {
              //ui->completedlabel->setText(query.value(1).toString());
              model2->setItem(j,new QStandardItem(query.value(1).toString()));
              j++;
            }
            else if(query.value(3).toString() == '1')
            {
              model1->setItem(i,new QStandardItem(query.value(1).toString()));
              i++;
            }
        }

        //ui->tasksdetail->setText(query.value(2).toString());

    }
}


void TomatoClock::on_Clear_clicked()
{
    QSqlQuery query;
    QString deletesql = QString("delete from information where conditions=0");
    bool success = query.exec(deletesql);
    if(success)
    {
        QMessageBox::about(NULL, "Reset", "Reset database success");
    }
    else {
        QMessageBox::about(NULL, "Reset", "error");
    }

}

void TomatoClock::on_completedlabel_clicked(const QModelIndex &index)
{
    theDeletes = index.data().toString();
}

void TomatoClock::on_Delete_clicked()
{
    qDebug()<<theDeletes;
    QSqlQuery query;
    QString deletesql = QString("delete from information where line='");
    deletesql += theDeletes;
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
