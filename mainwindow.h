#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "facture.h"

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

private:
    Ui::MainWindow *ui;
    Facture E;

};

#endif // MAINWINDOW_H
