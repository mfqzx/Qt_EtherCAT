
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <zmotion.h>
#include <zaux.h>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTime>
extern ZMC_HANDLE g_handle;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class zhou
{
public:
    float maichongdangliang;
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


    void keyPressEvent(QKeyEvent *event);

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

private:
    Ui::MainWindow *ui;
    QMessageBox war;
    zhou x;
    zhou y;
    zhou z;
    zhu_zhou aa;
    float P;
    float I;
    float D;
    int link_flag=0;
    int model_flag=0;
};

#endif // MAINWINDOW_H
