#include "notification.h"

#include <QSystemTrayIcon>
#include<QString>
notification::notification()
{

}


void notification::notification_ajoutProjet()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon("C:/Users/ALPHA/Documents/CONNEXION/Atelier_Connexion/res/aa.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Evenements ","Nouvelle Evenement ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::notification_supprimerProjet(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Evenements ","Un Evenement est supprimée",QSystemTrayIcon::Information,15000);

}

void notification::notification_modifierProjet(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Evenements ","Un Evenement est modifiée",QSystemTrayIcon::Information,15000);

}



