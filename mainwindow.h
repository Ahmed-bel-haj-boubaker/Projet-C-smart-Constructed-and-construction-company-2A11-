#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "employer.h"
#include "conges.h"
#include "arduino.h"
#include <QDialog>
#include <QSerialPort>
#include <QByteArray>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();


    void on_Modifier_clicked();

    void on_pb_supprimer_2_clicked();

    void on_recherche_mod_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    //void on_pushButton_3_clicked();

    //void on_pushButton_7_clicked();

    //void on_employer_2_clicked();

    void on_pushButton_16_clicked();

    //void on_comboBoxTri_activated(const QString &arg1);

    //void on_tab_9_customContextMenuRequested(const QPoint &pos);

    void on_print_clicked();

    void on_print_3_clicked();
    void on_print_7_clicked();

    void on_print_5_clicked();

    void on_print_4_clicked();



    void update_label_a_1 (); // slot permettant la mise à jour du label état de la lampe // ce slot est lancé à chaque réception d'un message de Arduino

    void on_pushButton_a_clicked (); // bouton ON

    void on_pushButton_a_2_clicked (); // bouton OFF

    void on_pushButton_a_3_clicked (); // bouton +

    void on_pushButton_a_4_clicked(); // bouton -

    void on_pushButton_11_clicked();

    void readSerial();
    void  updateTemperature(QString);

private:
    Ui::MainWindow *ui;
    employer e;
    conges v;

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
    QSerialPort *arduino;
        static const quint16 arduino_uno_vendor_id = 9025;
        static const quint16 arduino_uno_product_id = 67;
        QByteArray serialData;
        QString serialBuffer;
        QString parsed_data;
        double temperature_value;

};
#endif // MAINWINDOW_H
