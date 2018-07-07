#ifndef TOMATOCLOCK_H
#define TOMATOCLOCK_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
namespace Ui {
class TomatoClock;
}

class TomatoClock : public QMainWindow
{
    Q_OBJECT

public:
    void tasks_Show();


    explicit TomatoClock(QWidget *parent = 0);
    ~TomatoClock();


private slots:

    void on_Add_clicked();

    void on_Manage_clicked();

    void on_Done_clicked();

    void on_Start_clicked();

    void myslot1();
    void myslot2();
    void myslot3();



    void on_Stop_clicked();

    void on_Finish_clicked();

    void on_Clear_clicked();

    void on_completedlabel_clicked(const QModelIndex &index);

    void on_Delete_clicked();

private:
    Ui::TomatoClock *ui;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QString theDeletes;

};

#endif // TOMATOCLOCK_H
