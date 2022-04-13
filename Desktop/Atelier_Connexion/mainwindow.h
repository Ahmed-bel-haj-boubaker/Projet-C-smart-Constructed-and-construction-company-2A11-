#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    bool controlsaisie();
bool controlsaisie2();
    bool controlsaisie3();
    bool controlsaisie4();
    void on_pb_ajouter_clicked();

    void on_pb_afficher_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_le_modifier_clicked();

    void on_pushButton_clicked();

    void on_pb_ajouter_2_clicked();


    void on_pb_modifier_2_clicked();

    void on_le_supprimer_2_clicked();



    void on_pb_supprimer_2_clicked();




    void on_pb_afficher_2_clicked();



        void on_recherche_textChanged(const QString &arg1);




        void on_pb_trier_clicked();

        void on_pdf_clicked();

        void on_statistique_clicked();

        void on_stat_clicked();

        void on_afficher_clicked();

        void on_ajouter_clicked();

        void on_modifier_clicked();

        void on_supprimer_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
