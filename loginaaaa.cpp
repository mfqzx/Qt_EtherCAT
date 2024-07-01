#include "loginaaaa.h"
#include "ui_loginaaaa.h"
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QStyleOption>
#include <QDesktopServices>
#include <QUrl>
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
    //ui->widget_2->setStyleSheet(".QWidget{background-color:#FFFFFF;border-radius:6px;}");
    ui->widget_2->setGraphicsEffect(effect);
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
    this->close();
    bbba=new MainWindow;
    bbba->show();
}


void loginaaaa::on_pushButton_5_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/mfqzx?tab=repositories")));
}

