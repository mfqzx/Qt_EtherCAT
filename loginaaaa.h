#ifndef LOGINAAAA_H
#define LOGINAAAA_H

#include <QWidget>

#include "mainwindow.h"
#include <QMessageBox>
#include "dialog.h"
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
    void saveData();
private:
    void paintEvent(QPaintEvent *);
    Ui::loginaaaa *ui;
    MainWindow *bbba;
    Dialog *zhuce;
    QMessageBox wet;

};
extern QString username[1000];
extern QString pwd[1000];
#endif // LOGINAAAA_H
