#include "dialog.h"
#include "ui_dialog.h"
#include "loginaaaa.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    int temp1=0;
    QString temp2="";
    QString temp3="";
    for(int i=0;i<500;i++)
    {
        if(username[i].isEmpty())
        {
            temp1=i;
            break;
        }
    }
    qDebug()<<temp1;
    temp2=ui->lineEdit->text();
    username[temp1]=temp2;
    temp3=ui->lineEdit_2->text();
    pwd[temp1]=temp3;
    this->close();
}

