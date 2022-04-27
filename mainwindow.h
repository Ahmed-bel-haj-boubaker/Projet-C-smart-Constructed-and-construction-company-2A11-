#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
#include "projet.h"
#include"notification.h"
#include<QDate>
#include<QWidget>
#include"employer.h"
#include<QMediaPlayer>
#include"login.h"
#include"popup.h"
#include"materiel.h"
#include "arduino.h"
#include"client.h"
#include"rdv.h"
#include "facture.h"
#include"qrcode.h"
#include"reclamation.h"
#include <QIntValidator>

#include <QSerialPort>
#include <QByteArray>
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

//void update_label();

    void on_modifier_clicked();

    void on_supprimer_clicked();

    void on_rechercher_textChanged(const QString &arg1);

    void on_suiv1_clicked();

   // void on_suiv2_clicked();

  //  void on_suiv3_clicked();

    void on_suivi2_clicked();

    void on_tri_currentIndexChanged(int index);

    void on_pushButton_clicked();

  //  void on_filtre_currentIndexChanged(int index);

    //void on_filtre_currentIndexChanged(const QString &arg1);

    //void on_filtre_currentIndexChanged(QString nom_projet);

    //void on_sort_currentIndexChanged(int index);

   // void on_calcul_surface_clicked();
void stats(QString table,QString critere,int valeur1,int valeur2,QString unite);

private:
    Ui::MainWindow *ui;
  QSystemTrayIcon *notifier;
    projet P;
    notification N;
    PopUp *popUp;
    Materiel M ;
    QByteArray D; // variable contenant les données reçues
    Client C;
    Rdv R;

    Facture E;
    Arduino A;
Reclamation R1;

login *l;

QByteArray data; // variable contenant les données reçues

//Arduino A; // objet temporaire
QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    double temperature_value;
private slots:
///emna///
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

//void on_buzzer_clicked();
//void on_update_temperature_clicked();
//void on_pushButton_11_clicked();
 void on_pdf_clicked();
 void on_bouton_excel_clicked();
 void on_stat_client_clicked();
 void on_comboBox_activated(const QString &arg1);
void update_temperature();

void on_pb_alarm_clicked();

    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeSign();
    void ClearScreen();
    void MemoryClear();
    void MemoryRecall();
    void MemoryStore();
    void on_calculer_clicked();
    void on_stat_clicked();
    void on_traduction_currentIndexChanged(int index);
    void on_imprimer_clicked();
    void on_avant_clicked();
    void on_avant_2_clicked();
   // void on_tri_local_activated(const QString &arg1);
    void on_tri_local_currentIndexChanged(int);
   // void on_pushButton_2_clicked();
    void on_employer_clicked();
    void on_ajouter_Employer_clicked();
    void on_logOUT_clicked();
    void on_logOUT_2_clicked();
    void on_projet_clicked();
    void on_pushButton_14_clicked();
    void on_tableView_emploi_clicked(const QModelIndex &index);
    void on_dateTimeEdit_emploiS_dateTimeChanged(const QDateTime &dateTime);
    void on_calendarWidget_2_clicked(const QDate &date);
    void on_pushButton_emploi_goto_clicked();
    void on_dateTimeEdit_emploiE_dateTimeChanged(const QDateTime &dateTime);
    void on_pushButton_mdf_emploi_clicked();
    void on_suivi2_2_clicked();
    void on_avant_3_clicked();
    void on_tab_projet_clicked(const QModelIndex &index);
    void on_rechercher_local_textChanged(const QString &arg1);

    void on_notif_clicked();
    void on_materielle_clicked();



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
bool controlsaisie2();
bool controlsaisie3();
    void on_B_produit_Historique_2_clicked();
void statF(QString table,QString critere,int valeur1,int valeur2,QString unite);
    void on_B_produit_Imprimer_2_clicked();
    void on_suiv1_2_clicked();
    void on_avant_4_clicked();
    void on_suiv1_6_clicked();
    void on_avant_5_clicked();
    void on_suivi2_3_clicked();
   // void on_suiv1_5_clicked();
    void on_client_clicked();
    void on_pb_modifer_clicked();
    void on_avant_6_clicked();
    void on_pb_ajouter_fac_clicked();
    void on_modif_btn_clicked();
    void on_rechercher_fac_textChanged(const QString &arg1);
    void on_imprimer_fac_clicked();
    void on_stat_fac_clicked();
    void on_facture_clicked();
    void on_suiv1_3_clicked();
    void on_qr_clicked();
    void on_Supp_btn_clicked();
    void on_somme_clicked();
    void on_pb_ajouter_f_clicked();
    void on_pb_modifer_f_clicked();
    void on_le_supprimer_f_clicked();
    void on_pdf_f_clicked();
    void on_stat_four_clicked();
    void on_pb_trier_f_clicked();
    void on_recherche_f_textChanged(const QString &arg1);
    void on_ajouter_rec_clicked();
    void on_modif_rec_clicked();
void on_pushButton_12_clicked();



















void on_fournisseur_clicked();
void on_suiv1_7_clicked();
};

#endif // MAINWINDOW_H
