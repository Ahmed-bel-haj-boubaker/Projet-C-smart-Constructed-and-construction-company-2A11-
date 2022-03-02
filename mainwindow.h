#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
#include"projet.h"
#include<QMediaPlayer>
#include<QSound>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pb_ajouter_clicked();


    void on_pushButton_clicked();

    //void on_pushButton_3_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

  //  void on_recherche_editingFinished();

   // void on_recherche_textChanged(const QString &arg1);

    void on_lawej_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    projet P;
QMediaPlayer  play;

};

#endif // MAINWINDOW_H
