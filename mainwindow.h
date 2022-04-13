#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "rdv.h"
#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include "arduino.h"

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
    bool controlsaisie();
    bool controlsaisie1();
    void on_pb_ajouter_clicked();
    void on_le_supprimer_clicked();
    void on_pb_modifier_clicked();

    void on_pushButton_10_clicked();
    //void on_pushButton_11_clicked();

    //void on_pushButton_2_clicked();

    void on_pb_trier_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void on_pushButton_9_clicked();

    void on_buzzer_clicked();
    void on_update_temperature_clicked();
    void on_pushButton_11_clicked();
     void on_pdf_clicked();
     void on_bouton_excel_clicked();
     void on_stat_clicked();
     void on_comboBox_activated(const QString &arg1);
void update_temperature();
private:
    Ui::MainWindow *ui;
    Client C;
    Rdv R;

};

#endif // MAINWINDOW_H
