#include "notification.h"

#include <QSystemTrayIcon>
#include<QString>
notification::notification()
{

}


void notification::notification_ajoutProjet()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   notifyIcon->setIcon(QIcon(":/prefix/new/res/constop.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des des Projet ","Projet ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::notification_supprimerProjet(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

  notifyIcon->setIcon(QIcon(":/prefix/new/res/constop.png"));
  notifyIcon->show();
    notifyIcon->showMessage("Gestion des des Projet","Un Projet est supprimée",QSystemTrayIcon::Information,15000);

}

void notification::notification_modifierProjet(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

     notifyIcon->setIcon(QIcon(":/prefix/new/res/constop.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des des Projet ","Un Projet est modifiée",QSystemTrayIcon::Information,15000);

}



