#ifndef LOGINAAAA_H
#define LOGINAAAA_H

#include <QWidget>

#include "mainwindow.h"
namespace Ui {
class loginaaaa;
}

class loginaaaa : public QWidget
{
    Q_OBJECT

public:
    explicit loginaaaa(QWidget *parent = nullptr);
    ~loginaaaa();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    void paintEvent(QPaintEvent *);
    Ui::loginaaaa *ui;
    MainWindow *bbba;
};

#endif // LOGINAAAA_H
