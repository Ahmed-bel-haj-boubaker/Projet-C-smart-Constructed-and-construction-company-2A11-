#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
#include"projet.h"
#include<QDate>
#include<QWidget>
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
   // void on_stackedWidget_2_currentChanged(int arg1);

    void on_ajouter_clicked();



    void on_modifier_clicked();

    void on_supprimer_clicked();

    void on_rechercher_textChanged(const QString &arg1);

    void on_suiv1_clicked();

   // void on_suiv2_clicked();

    void on_suiv3_clicked();

    void on_suivi2_clicked();

    void on_tri_currentIndexChanged(int index);

    void on_pushButton_clicked();

  //  void on_filtre_currentIndexChanged(int index);

    //void on_filtre_currentIndexChanged(const QString &arg1);

    void on_filtre_currentIndexChanged(QString nom_projet);

private:
    Ui::MainWindow *ui;
    projet P;
};

#endif // MAINWINDOW_H
