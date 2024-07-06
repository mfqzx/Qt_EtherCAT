
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <zmotion.h>
#include <zaux.h>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTime>
#include <QLineEdit>
#include <QTimerEvent>
extern ZMC_HANDLE g_handle;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class zhou
{
public:
    float maichongdangliang;
    float fvspeed;
    float zhengxianwei;
    float fuxianwei;
    float zhengxianwei_IO;
    float fuxianwei_IO;
    float pos;

};

class zhu_zhou
{
public:
    float sudu;
    float max_sudu;
    float jiasudu;
    float jiansudu;
    float guodushijian;
    float paxingsshijian;
    float jiting_IO;
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ZMC_HANDLE g_handle;

private slots:
    void on_ButtonCS_clicked();

    void on_ButtonZD_clicked();

    void on_ButtonSD_clicked();

    void on_ButtonZZ_clicked();

    void on_comboBox_2_activated(int index);

    void on_pushButton_clicked();

    void timerEvent(QTimerEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

    void links();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_toolButton_W_pressed();

    void on_toolButton_W_released();

    void on_toolButton_S_pressed();

    void on_toolButton_S_released();

    void on_toolButton_A_pressed();

    void on_toolButton_A_released();

    void on_toolButton_D_pressed();

    void on_toolButton_D_released();

    void on_toolButton_H_pressed();

    void on_toolButton_H_released();

    void on_toolButton_L_pressed();

    void on_toolButton_L_released();

    void xqianjin();

    void xhoutui();

    void yqianjin();

    void yhoutui();

    void zqianjin();

    void zhoutui();

    void xting();

    void yting();

    void zting();

    void zhuzhourun();

    void zhuzhouting();

    void Sleep(int msec);

    void on_Button_BPQstart_clicked();

    void on_Button_BPQstop_clicked();

    void on_pushButton_7_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_clicked();

    void on_Button__clicked();

    void on_Button_start_clicked();
    void  command_G();
    void Pause();
    void Continue();
    void clean();
    void jiyi();
    void huifu();

    void on_Button_stop_clicked();

    void on_Button_continue_clicked();

    void on_Button_clean_clicked();

    void on_Button_jiyi_clicked();

    void on_Button_huifu_clicked();

private:
    Ui::MainWindow *ui;
    QMessageBox war;
    int m_timerid;//定时器返回值
    zhou x;
    zhou y;
    zhou z;
    zhu_zhou aa;
    float P;
    float I;
    float D;
    int link_flag=0;
    int model_flag=0;
    int g_command[2]={0,0};//8.3默认G00，默认没有出现G90/G91
    int g_0full=0;int g_1full=0;int g_mode=90;//默认坐标移动为绝对值
    int Modbus=2;
    float m_aspeed=100.0;
    float xyz_pos[3]={0.0,0.0,0.0};//目标点
    float daodianjiyi[3];
    bool  zhongduan_biaozhi;
     QTextCursor cursor;
        float hangshu=0;
    QString fileFull="No file";
        QFile* fileread;
    float iiiii=1; int row=0, lie=0;
    QTextCharFormat fmt;
      QLineEdit* lineedit_setspeed[6];
};

#endif // MAINWINDOW_H
