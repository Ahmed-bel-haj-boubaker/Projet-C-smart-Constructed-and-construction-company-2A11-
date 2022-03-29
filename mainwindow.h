#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "materiel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
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

  void on_E_produit_Reherche_textChanged(const QString &arg1);


  void on_B_produit_tri_textActivated(const QString &arg1);

  void on_B_produit_Imprimer_clicked();

  void on_B_produit_tri_activated();


  void on_B_produit_Historique_clicked();

  void on_B_produit_satistique_clicked();

  void on_B_produit_Historique_2_clicked();

private:
    Ui::MainWindow *ui;
    Materiel M ;
};

#endif // MAINWINDOW_H
