
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zaux.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(4);
    g_handle=nullptr;
    this->setWindowTitle("未连接控制器");
    QStringList IP;
    IP<<"127.0.0.1"<< "192.168.0.11";
    ui->comboBox_2->addItems(IP);
    ui->label_30->setText("请连接");
    ui->label_30->setStyleSheet("color: red");
    ui->ButtonZD->setEnabled(1);
    ui->ButtonSD->setEnabled(1);
    ui->toolButton_W->setShortcut(Qt::Key_W);
    ui->toolButton_S->setShortcut(Qt::Key_S);
    ui->X_plus->setStyleSheet("image: url(:/pic/checked.png)");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ButtonCS_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_ButtonZD_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_ButtonSD_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_ButtonZZ_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_comboBox_2_activated(int index)
{

}

// 连接
void MainWindow::on_pushButton_clicked()
{
    links();
}
// 连接函数定义
void MainWindow::links()
{
    char* buffer;
    int32 result;
    if(g_handle!=nullptr)
    {
        ZMC_Close(g_handle);
        g_handle=nullptr;
        return;
    }
    QString link_ip;
    link_ip=ui->comboBox_2->currentText();
    QByteArray a=link_ip.toUtf8();
    buffer=a.data();
    result=ZMC_OpenEth(buffer,&g_handle);
    if(result!=0)
    {
        g_handle=nullptr;
        war.setWindowTitle("提示");
        war.setText("连接失败！");
        war.exec();
        model_flag=0;
        return;
    }
    if(link_ip=="127.0.0.1")
    {

        model_flag=1;
        ui->label_30->clear();
        ui->label_30->setText("仿真模式！");

    }
    else
    {
        ui->label_30->clear();
        ui->label_30->setText("实机模式！");
        model_flag=2;
    }
    this->setWindowTitle("已连接"+link_ip);
    ui->pushButton->setEnabled(0);
    ui->pushButton_2->setEnabled(1);
    link_flag=1;
}
// 断开
void MainWindow::on_pushButton_2_clicked()
{
    if(g_handle!=nullptr)
    {
        ZMC_Close(g_handle);
        g_handle=nullptr;
        this->setWindowTitle("未连接控制器");
        ui->pushButton->setEnabled(1);
        ui->pushButton_2->setEnabled(0);
        link_flag=0;
        model_flag=0;
        return;
    }
}

// 参数设置保存
void MainWindow::on_pushButton_3_clicked()
{
    // x轴参数
    QString temp1[6];
    temp1[0]=ui->X_1->text();
    temp1[1]=ui->X_3->text();
    temp1[2]=ui->X_4->text();
    temp1[3]=ui->X_5->text();
    temp1[4]=ui->X_6->text();

    x.maichongdangliang=temp1[0].toFloat();
    x.zhengxianwei=temp1[1].toFloat();
    x.fuxianwei=temp1[2].toFloat();
    x.zhengxianwei_IO=temp1[3].toFloat();
    x.fuxianwei_IO=temp1[4].toFloat();

    // y轴参数
    QString temp2[6];
    temp2[0]=ui->Y_1->text();
    temp2[1]=ui->Y_2->text();
    temp2[2]=ui->Y_3->text();
    temp2[3]=ui->Y_7->text();
    temp2[4]=ui->Y_12->text();

    y.maichongdangliang=temp2[0].toFloat();
    y.zhengxianwei=temp2[1].toFloat();
    y.fuxianwei=temp2[2].toFloat();
    y.zhengxianwei_IO=temp2[3].toFloat();
    y.fuxianwei_IO=temp2[4].toFloat();

    // z轴参数
    QString temp3[6];
    temp3[0]=ui->Z_1->text();
    temp3[1]=ui->Z_2->text();
    temp3[2]=ui->Z_3->text();
    temp3[3]=ui->Z_4->text();
    temp3[4]=ui->Z_5->text();

    z.maichongdangliang=temp3[0].toFloat();
    z.zhengxianwei=temp3[1].toFloat();
    z.fuxianwei=temp3[2].toFloat();
    z.zhengxianwei_IO=temp3[3].toFloat();
    z.fuxianwei_IO=temp3[4].toFloat();

    // 主轴参数
    QString temp4[8];
    temp4[0]=ui->Zhu_1->text();
    temp4[1]=ui->Zhu_3->text();
    temp4[2]=ui->Zhu_4->text();
    temp4[3]=ui->Zhu_5->text();
    temp4[4]=ui->Zhu_6->text();
    temp4[5]=ui->Zhu_7->text();
    temp4[6]=ui->Zhu_8->text();

    aa.sudu=temp4[0].toFloat();
    aa.max_sudu=temp4[1].toFloat();
    aa.jiasudu=temp4[2].toFloat();
    aa.jiansudu=temp4[3].toFloat();
    aa.guodushijian=temp4[4].toFloat();
    aa.paxingsshijian=temp4[5].toFloat();
    aa.jiting_IO=temp4[6].toFloat();

    P=(ui->lineEdit->text()).toFloat();
    I=(ui->lineEdit_2->text()).toFloat();
    D=(ui->lineEdit_3->text()).toFloat();

    war.setWindowTitle("提示");
    war.setText("参数保存成功！");
    war.exec();

}

// 应用参数设置
void MainWindow::on_pushButton_10_clicked()
{

    if(link_flag!=1)
    {
        war.setWindowTitle("错误");
        war.setText("未连接控制器，请先连接！");
        war.exec();
        return ;
    }
    // 对x,y,z轴分别进行设置
    for(int i=0;i<3;i++)
    {
        if(model_flag==1)
        {
            ZAux_Direct_SetAtype(g_handle,i,0);             //
            ZAux_Direct_SetInvertStep(g_handle,i,1);        //
        }
        else if(model_flag==2)
        {
            ZAux_Direct_SetAtype(g_handle,i,65);            //
        }
    }
    // x轴参数写入：
    ZAux_Direct_SetSpeed(g_handle,0,aa.sudu);   // 设置速度
    ZAux_Direct_SetLspeed(g_handle,0,0);        // 设置初速度
    ZAux_Direct_SetAccel(g_handle,0,aa.jiasudu);    // 设置加速度
    ZAux_Direct_SetDecel(g_handle,0,aa.jiansudu);   // 设置减速度
    ZAux_Direct_SetSramp(g_handle,0,20);    // 设置梯形速度
    ZAux_Direct_SetUnits(g_handle,0,x.maichongdangliang);   // 设置脉冲当量
    ZAux_Direct_SetFsLimit(g_handle,0,x.zhengxianwei);      // 设置正限位
    ZAux_Direct_SetRsLimit(g_handle,0,-x.fuxianwei);        // 设置负限位
    ZAux_Direct_SetFwdIn(g_handle,0,x.zhengxianwei_IO);     // 设置正限位IO
    ZAux_Direct_SetRevIn(g_handle,0,x.fuxianwei_IO);        // 设置负限位IO
    ZAux_Direct_SetDatumIn(g_handle,0,0);                    // 回零IO
    ZAux_Direct_SetAlmIn(g_handle,0,-1);                    // 设置急停

    // y轴参数写入：
    ZAux_Direct_SetSpeed(g_handle,1,aa.sudu);   // 设置速度
    ZAux_Direct_SetLspeed(g_handle,1,0);        // 设置初速度
    ZAux_Direct_SetAccel(g_handle,1,aa.jiasudu);    // 设置加速度
    ZAux_Direct_SetDecel(g_handle,1,aa.jiansudu);   // 设置减速度
    ZAux_Direct_SetSramp(g_handle,1,20);    // 设置梯形速度
    ZAux_Direct_SetUnits(g_handle,1,y.maichongdangliang);   // 设置脉冲当量
    ZAux_Direct_SetFsLimit(g_handle,1,y.zhengxianwei);      // 设置正限位
    ZAux_Direct_SetRsLimit(g_handle,1,-y.fuxianwei);        // 设置负限位
    ZAux_Direct_SetFwdIn(g_handle,1,y.zhengxianwei_IO);     // 设置正限位IO
    ZAux_Direct_SetRevIn(g_handle,1,y.fuxianwei_IO);        // 设置负限位IO
    ZAux_Direct_SetDatumIn(g_handle,1,0);                    // 回零IO
    ZAux_Direct_SetAlmIn(g_handle,1,-1);                    // 设置急停

    // z轴参数写入：
    ZAux_Direct_SetSpeed(g_handle,2,aa.sudu);   // 设置速度
    ZAux_Direct_SetLspeed(g_handle,2,0);        // 设置初速度
    ZAux_Direct_SetAccel(g_handle,2,aa.jiasudu);    // 设置加速度
    ZAux_Direct_SetDecel(g_handle,2,aa.jiansudu);   // 设置减速度
    ZAux_Direct_SetSramp(g_handle,2,20);    // 设置梯形速度
    ZAux_Direct_SetUnits(g_handle,2,z.maichongdangliang);   // 设置脉冲当量
    ZAux_Direct_SetFsLimit(g_handle,2,z.zhengxianwei);      // 设置正限位
    ZAux_Direct_SetRsLimit(g_handle,2,-z.fuxianwei);        // 设置负限位
    ZAux_Direct_SetFwdIn(g_handle,2,z.zhengxianwei_IO);     // 设置正限位IO
    ZAux_Direct_SetRevIn(g_handle,2,z.fuxianwei_IO);        // 设置负限位IO
    ZAux_Direct_SetDatumIn(g_handle,2,0);                    // 回零IO
    ZAux_Direct_SetAlmIn(g_handle,2,-1);                    // 设置急停

    war.setText("11");
    war.exec();
}

// 待写，好像可以简化
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_A)
    {

    }

}

//x轴回0
void MainWindow::on_pushButton_4_clicked()
{
    ZAux_Direct_GetDpos(g_handle,0,&x.pos);//获得轴位置
    if(x.pos>0)
        ZAux_Direct_Singl_Datum(g_handle,0,19);
    else
        ZAux_Direct_Singl_Datum(g_handle,0,18);
}

//y轴回0
void MainWindow::on_pushButton_5_clicked()
{
    ZAux_Direct_GetDpos(g_handle,1,&y.pos);

    if(y.pos>0)
        ZAux_Direct_Singl_Datum(g_handle,1,19);

    else
        ZAux_Direct_Singl_Datum(g_handle,1,18);
}

//z轴回0
void MainWindow::on_pushButton_6_clicked()
{
    ZAux_Direct_GetDpos(g_handle,2,&z.pos);
    if(z.pos>0)
        ZAux_Direct_Singl_Datum(g_handle,2,19);

    else
        ZAux_Direct_Singl_Datum(g_handle,2,18);
}
//坐标置零
void MainWindow::on_pushButton_7_clicked()
{
    x.pos=0;
    y.pos=0;
    z.pos=0;
}
//三轴运动函数
void MainWindow::yqianjin(){
    ZAux_Direct_Singl_Vmove(g_handle,1,1);
}
void MainWindow::yhoutui(){
     ZAux_Direct_Singl_Vmove(g_handle,1,-1);
}
void MainWindow::xqianjin(){
    ZAux_Direct_Singl_Vmove(g_handle,0,1);
}
void MainWindow::xhoutui(){
    ZAux_Direct_Singl_Vmove(g_handle,0,-1);
}
void MainWindow::zqianjin(){
    ZAux_Direct_Singl_Vmove(g_handle,2,1);
}
void MainWindow::zhoutui(){
    ZAux_Direct_Singl_Vmove(g_handle,2,-1);
}
void MainWindow::xting(){
    ZAux_Direct_Singl_Cancel(g_handle,0,2);
}
void MainWindow::yting(){
    ZAux_Direct_Singl_Cancel(g_handle,1,2);
}
void MainWindow::zting(){
    ZAux_Direct_Singl_Cancel(g_handle,2,2);
}
//y轴前进
void MainWindow::on_toolButton_W_pressed()
{
    yqianjin();
}

void MainWindow::on_toolButton_W_released()
{
    yting();
}

//y轴后退
void MainWindow::on_toolButton_S_pressed()
{
    yhoutui();
}

void MainWindow::on_toolButton_S_released()
{
    yting();
}


//x轴前进
void MainWindow::on_toolButton_D_pressed()
{
    xqianjin();
}
void MainWindow::on_toolButton_D_released()
{
    xting();
}

//x轴后退
void MainWindow::on_toolButton_A_pressed()
{
    xhoutui();
}
void MainWindow::on_toolButton_A_released()
{
    xting();
}

//z轴升高
void MainWindow::on_toolButton_H_pressed()
{
    zqianjin();
}
void MainWindow::on_toolButton_H_released()
{
    zting();
}

//z轴降低
void MainWindow::on_toolButton_L_pressed()
{
    zhoutui();
}
void MainWindow::on_toolButton_L_released()
{
    zting();
}

//主轴运行
void MainWindow::zhuzhourun()
{
    QString pinlu;
    pinlu=ui->lineEdit_7->text();
    int m_freq(pinlu.toInt());
    ZAux_Modbus_Set4x_Long(g_handle,3,1,&m_freq);//频率寄存器111
    ZMC_Execute(g_handle, "MODBUSM_REGSET(100,1,3)",15,  NULL, 0);
    Sleep(150);
    if(ui->radioButton_3->isChecked()==1)//正向
    {
        ZMC_Execute( g_handle, "MODBUSM_REGSET(99,1,0)",15,  NULL, 0);
    }
    else if(ui->radioButton_4->isChecked()==1)//反向
    {
        ZMC_Execute( g_handle, "MODBUSM_REGSET(99,1,2)", 15, NULL, 0);
    }
}
//
void MainWindow::zhuzhouting()
{
     ZMC_Execute( g_handle, "MODBUSM_REGSET(99,1,1)", 15, NULL, 0);
}


void MainWindow::on_Button_BPQstart_clicked()
{
    zhuzhourun();

}

void MainWindow::on_Button_BPQstop_clicked()
{
    zhuzhouting();
}
void MainWindow::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



