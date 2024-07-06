
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zaux.h"
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextCodec>
#include <QTextBlock>
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
    //ui->toolButton_W->setShortcut(Qt::Key_W);
    //ui->X_plus->setStyleSheet("image: url(:/pic/green.png)");

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
    if(ui->pushButton_10->isEnabled()==1)
    {
        war.setWindowTitle("提示");
        war.setText("请先应用设置！");
        war.exec();
    }
    else
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
    m_timerid=startTimer(5);
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
    qDebug()<<x.fuxianwei;
    war.setWindowTitle("提示");
    war.setText("参数保存成功！");
    war.exec();
    ui->pushButton_3->setEnabled(0);

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
    ZAux_Direct_SetRsLimit(g_handle,0,x.fuxianwei);        // 设置负限位
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
    ZAux_Direct_SetRsLimit(g_handle,1,y.fuxianwei);        // 设置负限位
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
    ZAux_Direct_SetRsLimit(g_handle,2,z.fuxianwei);        // 设置负限位
    ZAux_Direct_SetFwdIn(g_handle,2,z.zhengxianwei_IO);     // 设置正限位IO
    ZAux_Direct_SetRevIn(g_handle,2,z.fuxianwei_IO);        // 设置负限位IO
    ZAux_Direct_SetDatumIn(g_handle,2,0);                    // 回零IO
    ZAux_Direct_SetAlmIn(g_handle,2,-1);                    // 设置急停
    war.setWindowTitle("提示");
    war.setText("参数应用成功！");
    war.exec();
    ui->pushButton_10->setEnabled(0);
}
int wKeyPressed=0;
// 待写，好像可以简化
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W && !event->isAutoRepeat())
    {

        if (!wKeyPressed)
        {
            ui->toolButton_W->setStyleSheet("border-image: url(:/pic/up.png);border-radius:15px;background-color: rgba(227, 175, 172, 200);");
            wKeyPressed = 1;
            yqianjin();
        }
    }
    else if (event->key() == Qt::Key_S && !event->isAutoRepeat())
    {
        if (!wKeyPressed)
        {
            ui->toolButton_S->setStyleSheet("border-image: url(:/pic/down.png);border-radius:15px;background-color: rgba(227, 175, 172, 200);");
            wKeyPressed = 1;
            yhoutui();
        }
    }
    else if (event->key() == Qt::Key_A && !event->isAutoRepeat())
    {
        if (!wKeyPressed)
        {
            ui->toolButton_A->setStyleSheet("border-image: url(:/pic/left.png);border-radius:15px;background-color: rgba(227, 175, 172, 200);");
            wKeyPressed = 1;
            xhoutui();
        }
    }
    else if (event->key() == Qt::Key_D && !event->isAutoRepeat())
    {
        if (!wKeyPressed)
        {
            ui->toolButton_D->setStyleSheet("border-image: url(:/pic/right.png);border-radius:15px;background-color: rgba(227, 175, 172, 200);");
            wKeyPressed = 1;
            xqianjin();
        }
    }
    else if (event->key() == Qt::Key_H && !event->isAutoRepeat())
    {
        if (!wKeyPressed)
        {
            ui->toolButton_H->setStyleSheet("border-image: url(:/pic/high.png);border-radius:15px;background-color: rgba(227, 175, 172, 200);");
            wKeyPressed = 1;
            zqianjin();
        }
    }
    else if (event->key() == Qt::Key_L && !event->isAutoRepeat())
    {
        if (!wKeyPressed)
        {
            ui->toolButton_L->setStyleSheet("border-image: url(:/pic/low.png);border-radius:15px;background-color: rgba(227, 175, 172, 200);");
            wKeyPressed = 1;
            zhoutui();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_W||event->key() == Qt::Key_S) && !event->isAutoRepeat())
    {
        ui->toolButton_W->setStyleSheet(
           "#toolButton_W{"
                "border-image: url(:/pic/up.png);"
                "border-radius:15px;"
                "background-color: rgba(100, 150, 200, 100);"
            "}"
            "#toolButton_W:pressed{"
                " border:3px solid #b1764c;"
                "    color:#dfdcd7;"
                "background-color: rgba(144, 144, 144, 200);"
            "}"
            );
        ui->toolButton_S->setStyleSheet(
            "#toolButton_S{"
            "border-image: url(:/pic/down.png);"
            "border-radius:15px;"
            "background-color: rgba(100, 150, 200, 100);"
            "}"
            "#toolButton_S:pressed{"
            " border:3px solid #b1764c;"
            "    color:#dfdcd7;"
            "background-color: rgba(144, 144, 144, 200);"
            "}"
            );
        wKeyPressed = false;
        yting();
    }
    else if ((event->key() == Qt::Key_A||event->key() == Qt::Key_D) && !event->isAutoRepeat())
    {
        ui->toolButton_A->setStyleSheet(
            "#toolButton_A{"
            "border-image: url(:/pic/left.png);"
            "border-radius:15px;"
            "background-color: rgba(100, 150, 200, 100);"
            "}"
            "#toolButton_A:pressed{"
            " border:3px solid #b1764c;"
            "    color:#dfdcd7;"
            "background-color: rgba(144, 144, 144, 200);"
            "}"
            );
        ui->toolButton_D->setStyleSheet(
            "#toolButton_D{"
            "border-image: url(:/pic/right.png);"
            "border-radius:15px;"
            "background-color: rgba(100, 150, 200, 100);"
            "}"
            "#toolButton_D:pressed{"
            " border:3px solid #b1764c;"
            "    color:#dfdcd7;"
            "background-color: rgba(144, 144, 144, 200);"
            "}"
            );
        wKeyPressed = false;
        xting();
    }
    else if ((event->key() == Qt::Key_H||event->key() == Qt::Key_L) && !event->isAutoRepeat())
    {
        ui->toolButton_H->setStyleSheet(
            "#toolButton_H{"
            "border-image: url(:/pic/high.png);"
            "border-radius:15px;"
            "background-color: rgba(100, 150, 200, 100);"
            "}"
            "#toolButton_H:pressed{"
            " border:3px solid #b1764c;"
            "    color:#dfdcd7;"
            "background-color: rgba(144, 144, 144, 200);"
            "}"
            );
        ui->toolButton_L->setStyleSheet(
            "#toolButton_L{"
            "border-image: url(:/pic/low.png);"
            "border-radius:15px;"
            "background-color: rgba(100, 150, 200, 100);"
            "}"
            "#toolButton_L:pressed{"
            " border:3px solid #b1764c;"
            "    color:#dfdcd7;"
            "background-color: rgba(144, 144, 144, 200);"
            "}"
            );
        wKeyPressed = false;
        zting();
    }


}

int states_flag[3];

void MainWindow::timerEvent(QTimerEvent *event)
{

    float bbbb;
    if(m_timerid == event->timerId())
    {
        int idle[3] = {1, 1, 1};
        ZAux_Direct_GetIfIdle(g_handle,0,&idle[0]);//获得x轴状态
            if(idle[0])
            {
                ui->X_ZT->setText("停止");
            }
            else
            {
                ui->X_ZT->setText("运行");
            }
        ZAux_Direct_GetDpos(g_handle, 0, &x.pos);
        ui->X_ZB->setText(QString("%1mm").arg(x.pos));
        ZAux_Direct_GetMspeed(g_handle, 0, &x.fvspeed);
        ui->X_SD->setText(QString("%1mm/s").arg(x.fvspeed));

        ZAux_Direct_GetIfIdle(g_handle,1,&idle[1]);//获得y轴状态
        if(idle[1])
        {
            ui->Y_ZT->setText("停止");
        }
        else
        {
            ui->Y_ZT->setText("运行");
        }
        ZAux_Direct_GetDpos(g_handle, 1, &y.pos);
        ui->Y_ZB->setText(QString("%1mm").arg(y.pos));
        ZAux_Direct_GetMspeed(g_handle, 1, &y.fvspeed);
        ui->Y_SD->setText(QString("%1mm/s").arg(y.fvspeed));

        ZAux_Direct_GetIfIdle(g_handle,2,&idle[2]);//获得z轴状态
        if(idle[2])
        {
            ui->Z_ZT->setText("停止");
        }
        else
        {
            ui->Z_ZT->setText("运行");
        }
        ZAux_Direct_GetDpos(g_handle, 2, &z.pos);
        ui->Z_ZB->setText(QString("%1mm").arg(z.pos));
        ZAux_Direct_GetMspeed(g_handle, 2, &z.fvspeed);
        ui->Z_SD->setText(QString("%1mm/s").arg(z.fvspeed));

        if(zhongduan_biaozhi==1&&idle[0]&&idle[1]&&idle[2])
        {
            if(fileFull=="No file"){ui->textedit_file->setPlainText("No file");}
            else
            {
                QTextCodec *codec = QTextCodec::codecForName("GBK");//指定为GBK,因为file.readLine()无法读取中文

                static char* fileat;//用来指向每行的某个字符
                static QString str;


                if(iiiii<=hangshu)
                {
                    ui->textedit_file->setTextColor("black");
                    fmt.setForeground(QColor(Qt::green));
                    //移动光标到某行行首
                    QTextBlock block = ui->textedit_file->document()->findBlockByNumber(iiiii-1);
                    ui->textedit_file->setTextCursor(QTextCursor(block));
                    //上色
                    cursor = ui->textedit_file->textCursor();
                    cursor.select(QTextCursor::LineUnderCursor);   //选中要着色的内容
                    cursor.mergeCharFormat(fmt);    //设置文本格式
                    cursor.clearSelection(); //撤销选中
                    //获取光标所在行列
                    row=cursor.blockNumber();
                    lie=cursor.columnNumber();
                    //qDebug()<<row<<lie;
                    //读取一行文本数据
                    QByteArray lineread = fileread->readLine();
                    //将读取到的行数据转换为Unicode
                    str = codec->toUnicode(lineread);       //文件每一行内容
                    //qDebug()<<str;
                    QByteArray ba = str.toUtf8();
                    fileat = ba.data();
                    //qDebug()<<fileat;
                    for(;*fileat;fileat++)//依次对各个字符进行解析
                    {
                        switch(*fileat)
                        {
                        case 'G':
                            if(g_0full==0)
                            {   g_command[0] = atoi(fileat+1);g_0full=1;}
                            else if(g_1full==0)
                            {   g_command[1]= atoi(fileat+1); g_1full=1;}
                            break;
                        case 'F':
                            m_aspeed  = atof(fileat+1);
                            break;
                        case 'X':
                            xyz_pos[0] = atof(fileat+1);
                            break;
                        case 'Y':
                            xyz_pos[1] = atof(fileat+1);
                            break;
                        case 'Z':
                            xyz_pos[2] = atof(fileat+1);
                            break;
                        case'M':
                            Modbus=atoi(fileat+1);//command_M();//开刀或关刀
                        default: break;

                        }
                    }

                    ui->num_yiyongshijian->setText(QString::number(iiiii));//已用时间
                    ui->num_shengyushijian->setText(QString::number(hangshu-iiiii));//剩余时间
                    bbbb=(iiiii/hangshu)*100;

                    QString ccc=QString::number(bbbb,'f',2);
                    ui->num_jindu->setText(ccc+"%");

                    iiiii++;

                    //command_G();//运行对应运动函数

                    g_0full=0;
                    g_1full=0;
                }
                ui->textedit_file->setTextColor("black");
            }
        }

    }
    float zhengxianwei;
    float fuxianwei;
    ZAux_Direct_GetFsLimit(g_handle,0,&zhengxianwei);//x轴限位判断小灯报警
    ZAux_Direct_GetRsLimit(g_handle,0,&fuxianwei);

    if(x.pos>zhengxianwei)
    {
        states_flag[0]=1;
        ui->X_plus->setStyleSheet("image: url(:/pic/red.png)");
    }
    else if(x.pos<fuxianwei)
    {
        states_flag[0]=1;
        ui->X_sub->setStyleSheet("image: url(:/pic/red.png)");
    }
    else if(x.pos<zhengxianwei&&x.pos>fuxianwei)
    {
        states_flag[0]=-1;
        ui->X_plus->setStyleSheet("image: url(:/pic/green.png)");
        ui->X_sub->setStyleSheet("image: url(:/pic/green.png)");
    }
    ZAux_Direct_GetFsLimit(g_handle,1,&zhengxianwei);//y轴限位判断小灯报警
    ZAux_Direct_GetRsLimit(g_handle,1,&fuxianwei);
    if(y.pos>zhengxianwei)
    {

        states_flag[1]=1;
        ui->Y_plus->setStyleSheet("image: url(:/pic/red.png)");
    }
    else if(y.pos<fuxianwei)
    {
        states_flag[1]=1;
        ui->Y_sub->setStyleSheet("image: url(:/pic/red.png)");
    }
    else if(y.pos<zhengxianwei&&y.pos>fuxianwei)
    {
        states_flag[1]=-2;
        ui->Y_plus->setStyleSheet("image: url(:/pic/green.png)");
        ui->Y_sub->setStyleSheet("image: url(:/pic/green.png)");
    }
    ZAux_Direct_GetFsLimit(g_handle,2,&zhengxianwei);//z轴限位判断小灯报警
    ZAux_Direct_GetRsLimit(g_handle,2,&fuxianwei);
    if(z.pos>zhengxianwei)
    {
        states_flag[2]=1;
        ui->Z_plus->setStyleSheet("image: url(:/pic/red.png)");
        ui->STOP->setStyleSheet("image: url(:/red.png)");
    }
    else if(z.pos<fuxianwei)
    {
        states_flag[2]=1;
        ui->Z_sub->setStyleSheet("image: url(:/pic/red.png)");
    }
    else if(z.pos<zhengxianwei&&z.pos>fuxianwei)
    {
        states_flag[2]=-3;
        ui->Z_plus->setStyleSheet("image: url(:/pic/green.png)");
        ui->Z_sub->setStyleSheet("image: url(:/pic/green.png)");
    }
    if(states_flag[0]==-1&&states_flag[1]==-2&&states_flag[2]==-3)
    {
        ui->STOP->setStyleSheet("image: url(:/pic/green.png)");
    }
    else
    {
        ui->STOP->setStyleSheet("image: url(:/pic/red.png)");
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
    ZMC_Execute(g_handle,"MPOS=0,0,0",10,nullptr,0);
    ZMC_Execute(g_handle,"DPOS=0,0,0",10,nullptr,0);
}
//三轴运动函数
void MainWindow::yqianjin(){
    qDebug()<<"www";
    ZAux_Direct_Singl_Vmove(g_handle,1,1);
}
void MainWindow::yhoutui(){
    qDebug()<<"sss";
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
    qDebug()<<"yting";
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

void MainWindow::on_checkBox_2_clicked()//限位反转
{
    int ionum[6];
    ionum[0]=x.zhengxianwei_IO;
    ionum[1]=x.fuxianwei_IO;
    ionum[2]=y.zhengxianwei_IO;
    ionum[3]=y.fuxianwei_IO;
    ionum[4]=z.zhengxianwei_IO;
    ionum[5]=z.fuxianwei_IO;
    if(ui->checkBox_2->isChecked()==1)
    {
        for(int i=0;i<=5;i++){
            ZAux_Direct_SetInvertIn(g_handle,ionum[i],1);
        }
        ui->checkBox_2->clearFocus();
    }
    else if(ui->checkBox_2->isChecked()==0)
    {
        for(int i=0;i<=5;i++){
            ZAux_Direct_SetInvertIn(g_handle,ionum[i],0);
        }
    }
}


void MainWindow::on_checkBox_clicked()//制动反转
{
    if(ui->checkBox->isChecked()==1)
    {
        int ionum=-1;
        ZAux_Direct_SetInvertIn(g_handle,ionum,1);
    }
    if(ui->checkBox->isChecked()==0)
    {
        int ionum=-1;
        ZAux_Direct_SetInvertIn(g_handle,ionum,0);
    }
}
//导入文件

void MainWindow::on_Button__clicked()
{
    g_command[0]=0;
    g_command[1]=0;//8.3默认G00
    g_0full=0; g_1full=0; g_mode=90;//默认没有出现G90/G91,默认坐标移动为绝对值
    m_aspeed=100.0;
    xyz_pos[0]=0.0;//目标点
    xyz_pos[1]=0.0;
    xyz_pos[2]=0.0;

    zhongduan_biaozhi=0;
    hangshu=0;
    ui->num_jindu->setText("0");
    ui->num_yiyongshijian->setText(QString::number(0));//已用时间
    ui->num_shengyushijian->setText(QString::number(0));//剩余时间
    ui->num_daimazongshu->setText(QString::number(0));//显示当前文件行数
    ui->textedit_file->clear();
    QString fileName, filePath,fileSuffix;
    QFileInfo fileinfo;
    fileFull = QFileDialog::getOpenFileName(this,tr("file"),"/",tr("text(*.tap)"));  //获取整个文件名，打开tap文件
    //fileFull = E:\QtCode\newExample\myTry\新建文本文档.txt

    //获取文件信息
    fileinfo = QFileInfo(fileFull);

    //获取文件名字
    fileName = fileinfo.fileName();

    //获取文件后缀
    fileSuffix = fileinfo.suffix();

    //获取文件绝对路径
    filePath = fileinfo.absolutePath();
    if(!fileFull.isNull())
    {
        ui->Button_start->setEnabled(true);
        ui->Button_stop->setEnabled(true);
       ui->Button_continue->setEnabled(true);
       ui->Button_clean->setEnabled(true);
        ui->Button_jiyi->setEnabled(true);
       ui->Button_huifu->setEnabled(true);
        QFile file(fileFull);//通过文件路径，来获取文件
        if(!file.open(QFile::ReadOnly ))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);

        ui->textedit_file->setText(fileFull);
        //逐行读取文件并放入wen'ben'kuan文本框
        QTextCodec *codec = QTextCodec::codecForName("GBK");//指定为GBK,因为file.readLine()无法读取中文
        while (!file.atEnd())
        {

            //读取一行文本数据
            QByteArray line = file.readLine();
            //将读取到的行数据转换为Unicode
            QString str = codec->toUnicode(line);       //文件每一行内容
            //qDebug() << str;

            ui->textedit_file->insertPlainText(str);//追加放入文本框②

            hangshu++;
        }
        file.close();
        ui->num_daimazongshu->setText(QString::number(hangshu));//显示当前文件行数

    }
    else
    {
        qDebug()<<"cancel";
        fileFull="No file";
    }

}


//开始制作
void MainWindow::on_Button_start_clicked()
{
    zhongduan_biaozhi=1;
    iiiii=1;
    ui->textedit_file->moveCursor(QTextCursor::Start);//进度条滚到顶

    //通过文件路径，来获取文件
    fileread=new QFile(fileFull);
    if(!fileread->open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(fileread->errorString()));
        return;
    }
    //显示初始化
    hangshu=0;
    ui->num_jindu->setText(0);
    ui->num_yiyongshijian->setText(QString::number(0));//已用时间
    ui->num_shengyushijian->setText(QString::number(0));//剩余时间
    ui->num_daimazongshu->setText(QString::number(0));//显示当前文件行数
    ui->textedit_file->clear();

    if(!fileFull.isNull())
    {

        QFile file(fileFull);//通过文件路径，来获取文件
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);


        //逐行读取文件并放入wen'ben'kuan文本框
        QTextCodec *codec = QTextCodec::codecForName("GBK");//指定为GBK,因为file.readLine()无法读取中文
        while (!file.atEnd())
        {

            //读取一行文本数据
            QByteArray line = file.readLine();
            //将读取到的行数据转换为Unicode
            QString str = codec->toUnicode(line);       //文件每一行内容
            ui->textedit_file->insertPlainText(str);//追加放入文本框②
            hangshu++;
        }
        //  file.close();
        ui->num_daimazongshu->setText(QString::number(hangshu));//显示当前文件行数
    }
    else
    {
        fileFull="No file";
    }

}
void MainWindow::command_G()
{
    int iiii=3; float poslist[3];
    if(g_1full==0)
    {
        switch(g_command[0])
        {
        case 0:
            //hcy*********************************************************************************开始
            while(iiii){
                poslist[iiii-1]=xyz_pos[iiii-1] ;
                float s(lineedit_setspeed[1]->text().toFloat()) ;
                if(m_aspeed>s)
                { m_aspeed=s;}

                ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度

                iiii--;
            }
            switch(g_mode)
            {
            case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
            case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
            default:break;
            }
            //qDebug()<<poslist;
            //qDebug()<<g_mode;
            //glwidget->g_mode00or01=0;
            break;

        case 1:
            while(iiii){
                poslist[iiii-1]=xyz_pos[iiii-1] ;
                float s(lineedit_setspeed[0]->text().toFloat()) ;
                if(m_aspeed>s)
                { m_aspeed=s;}
                ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度


                iiii--;
            }
            switch(g_mode)
            {
            case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
            case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
            default:break;
            }
            //qDebug()<<poslist;
            //qDebug()<<g_mode;
            //glwidget->g_mode00or01=1;
            break;

        default:break;
            //hcy*********************************************************************************结束
        }
    }
    else if(g_1full==1)
    {
        switch(g_command[0])
        {
        case 90:
            g_mode=90;
            switch(g_command[1])
            {
            case 0:
                //hcy*********************************************************************************开始
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[1]->text().toFloat()) ;
                    if(m_aspeed>s)
                    { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度
                    //if(m_aspeed)

                    iiii--;
                }
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                //qDebug()<<g_mode;
                //glwidget->g_mode00or01=0;
                break;

            case 1:
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[0]->text().toFloat()) ;
                    if(m_aspeed>s)
                    { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度


                    iiii--;
                }
                //qDebug()<<poslist;
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                //qDebug()<<g_mode;
                //glwidget->g_mode00or01=1;
                break;

            default:break;
                //hcy*********************************************************************************结束
            }
            break;

        case 91:
            g_mode=91;
            switch(g_command[1])
            {
            case 0:
                //hcy*********************************************************************************开始
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[1]->text().toFloat()) ;
                    if(m_aspeed>s)
                    { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度

                    iiii--;
                }
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                // qDebug()<<g_mode;
                //glwidget->g_mode00or01=0;
                break;

            case 1:
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[0]->text().toFloat()) ;
                    if(m_aspeed>s)
                    { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度


                    iiii--;
                }
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                //qDebug()<<g_mode;
                //glwidget->g_mode00or01=1;
                break;

            default:break;
                //hcy*********************************************************************************结束
            }
            break;

        default:break;
        }
    }
}
//暂停



void MainWindow::Pause()
{
    zhongduan_biaozhi=0;
    ZAux_Direct_MovePause(g_handle,0);
    ui->Button_clean->setEnabled(false);
    ui->Button_start->setEnabled(false);
    ui->Button_huifu->setEnabled(false);//8.11
}
void MainWindow::Continue()
{
    zhongduan_biaozhi=1;
    ZAux_Direct_MoveResume(g_handle);
    ui->Button_clean->setEnabled(true);
    ui->Button_start->setEnabled(true);
    ui->Button_huifu->setEnabled(true);
}

void MainWindow::clean()
{
    float poslist[3]={0,0,0};
    ZAux_Direct_MoveAbs(g_handle,3,poslist);


}

void MainWindow::jiyi()
{
    float fdpos(0);
    for(int i=0;i<3;i++)
    {
        ZAux_Direct_GetDpos(g_handle,i,&fdpos);//获得轴位置
        daodianjiyi[i]=fdpos ;
    }
}
void MainWindow::huifu()
{
    ZAux_Direct_MoveAbs(g_handle,3,daodianjiyi);
}

void MainWindow::on_Button_stop_clicked()
{
    Pause();
}


void MainWindow::on_Button_continue_clicked()
{
    Continue();
}


void MainWindow::on_Button_clean_clicked()
{
    clean();
}


void MainWindow::on_Button_jiyi_clicked()
{
    jiyi();
}


void MainWindow::on_Button_huifu_clicked()
{
    huifu();
}

