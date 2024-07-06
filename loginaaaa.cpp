#include "loginaaaa.h"
#include "ui_loginaaaa.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QStyleOption>
#include <QDesktopServices>
#include <QUrl>
#include <QPushButton>
#include <QDebug>
QString username[1000];
QString pwd[1000];
loginaaaa::loginaaaa(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginaaaa)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,1);
    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(ui->widget_2);
    effect->setOffset(0, 0);//设置阴影距离
    effect->setColor(QColor(0,0,0,150));//设置阴影颜色
    effect->setBlurRadius(25);//设置阴影圆角
    ui->widget_2->setGraphicsEffect(effect);
    username[0]="mfq";
    pwd[0]="123456";
    username[1]="lckn";
    pwd[1]="111111";

    QFile file("user_data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int index = 0;
        while (!in.atEnd() && index < 500) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 2) {
                username[index] = fields[0];
                pwd[index] = fields[1];
                ++index;
            }
        }
        file.close();
    } else {
        qDebug() << "Failed to open file for reading";
    }
}

loginaaaa::~loginaaaa()
{
    delete ui;
}

void loginaaaa::paintEvent(QPaintEvent *)
{
    QStyleOption opt;

    opt.initFrom(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);


}

void loginaaaa::on_pushButton_3_clicked()
{
    this->close();
}




void loginaaaa::on_pushButton_clicked()
{

}


void loginaaaa::on_pushButton_6_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/mfqzx?tab=repositories")));
}


void loginaaaa::on_pushButton_4_clicked()
{
    QString temp_name;
    QString temp_pwd;
    bool login=false;
    bool cbx=false;
    int iii=0;
    if(!ui->lineEdit->text().isEmpty())
    {
        temp_name=ui->lineEdit->text();
        for(int i=0;i<500;i++)
        {
            if(username[i]==temp_name)
            {
                iii=i;
                cbx=true;
                break;
            }
        }
            if(cbx)
            {
                if(!ui->lineEdit_2->text().isEmpty())
                {
                    temp_pwd=ui->lineEdit_2->text();
                    if(pwd[iii]==temp_pwd)
                    {
                        login=true;
                    }
                    else
                    {
                        wet.setWindowTitle("提示");
                        wet.setText("密码错误，请检查！");
                        wet.exec();
                    }
                }
            }
            else
            {
                wet.setWindowTitle("提示");
                wet.setText("未找到用户，是否先注册？");
                wet.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
                wet.setDefaultButton(QMessageBox::Ok);
                QAbstractButton *okAbstractButton=  wet.button(QMessageBox::Ok);
                QPushButton *okButton = qobject_cast<QPushButton*>(okAbstractButton);
                if(okButton)
                {
                    okButton->setText("注册");
                }
                int ret=wet.exec();
                if(ret)
                {
                    zhuce=new Dialog;
                    zhuce->show();
                }

            }

    }
    else
    {
        wet.setWindowTitle("提示");
        wet.setText("请输入用户名！");
        wet.exec();
    }

    if(login)
    {
        this->close();
        saveData();
        bbba=new MainWindow;
        bbba->show();
    }

}

void loginaaaa::saveData() {
    QFile file("user_data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing";
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < 500; ++i) {
        if (!username[i].isEmpty()) {
            out << username[i] << "," << pwd[i] << "\n";
        }
    }

    file.close();
}

void loginaaaa::on_pushButton_5_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/mfqzx?tab=repositories")));
}

