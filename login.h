#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>
#include <QtWidgets/QMessageBox>
#include <QDialog>
#include"ui_login.h"
#include <QMainWindow>
#include<QPropertyAnimation>
#include<QTimer>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void on_LoginB_clicked();

    void on_actionCheck_Data_Base_triggered();
    void on_actionSettings_triggered();

private slots:
    void on_valider_clicked();

    void on_pushButton_clicked();

    void on_valider_2_clicked();

private:
    QTimer *delay;
    Ui::login *ui;
    QPropertyAnimation *animation;
};

#endif // LOGIN_H
