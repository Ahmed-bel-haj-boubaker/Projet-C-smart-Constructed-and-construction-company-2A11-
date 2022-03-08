#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "facture.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
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
    void on_pb_ajouter_clicked();

    void on_Supp_btn_clicked();

    void on_modif_btn_clicked();

    void on_rechercher_textChanged(const QString &arg1);

    void on_tri_currentIndexChanged(int index);

    void on_suiv1_clicked();

    void on_imprimer_clicked();

 //   void on_calcul_clicked();

   // void on_pushButton_Mail_2_clicked();

void statF(QString,QString ,int ,int,QString);

private:
    Ui::MainWindow *ui;
    Facture E;
private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeSign();
    void ClearScreen();
    void MemoryClear();
    void MemoryRecall();
    void MemoryStore();
    void on_calcul_clicked();
    void on_statF_clicked();
    void on_pb_ajouter_2_clicked();
    void on_Supp_btn_2_clicked();
};

#endif // MAINWINDOW_H
