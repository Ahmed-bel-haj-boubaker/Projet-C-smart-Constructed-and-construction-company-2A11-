#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "materiel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

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
  void on_B_produit_ajouter_clicked();

  void on_B_produit_supprimer_clicked();

  void on_B_produit_Afficher_clicked();

  void on_B_produit_Modifier_clicked();

private:
    Ui::MainWindow *ui;
    Materiel M ;
};

#endif // MAINWINDOW_H
