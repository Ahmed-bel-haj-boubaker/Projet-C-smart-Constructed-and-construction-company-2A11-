#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT += core quick
QT       += multimedia
QT       += core gui network
QT += core gui charts
QT += core gui sql printsupport multimedia serialport
QT += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    arduino.cpp \
    client.cpp \
    employer.cpp \
    facture.cpp \
    fournisseur.cpp \
    login.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    materiel.cpp \
    notification.cpp \
    popup.cpp \
    projet.cpp \
    qrcode.cpp \
    rdv.cpp \
    reclamation.cpp

HEADERS += \
    arduino.h \
    client.h \
    employer.h \
    facture.h \
    fournisseur.h \
    login.h \
        mainwindow.h \
    connection.h \
    materiel.h \
    notification.h \
    popup.h \
    projet.h \
    qrcode.h \
    rdv.h \
    reclamation.h

FORMS += \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    res/2205928-icone-de-facture-de-paiement-gratuit-vectoriel-removebg-preview.png \
    res/2205928-icone-de-facture-de-paiement-gratuit-vectoriel.jpg \
    res/272658887_1094234024663786_8066416847757236482_n (1).png \
    res/272658887_1094234024663786_8066416847757236482_n (1).png \
    res/272658887_1094234024663786_8066416847757236482_n (1).png \
    res/272658887_1094234024663786_8066416847757236482_n.png \
    res/80-804604_retro-wallpaper-hd.jpg \
    res/84380.png \
    res/CONSTOP.mp4 \
    res/Hexa_High__2_-removebg-preview (1).png \
    res/Hexa_High__2_-removebg-preview (1).png \
    res/Hexa_High__2_-removebg-preview (1).png \
    res/arrow-right.png \
    res/calcul.png \
    res/circle-check-solid.png \
    res/click.mp3 \
    res/constop.png \
    res/download (1).png \
    res/download (1).png \
    res/download (1).png \
    res/download.png \
    res/edit.png \
    res/home.png \
    res/home41-removebg-preview.png \
    res/home41.png \
    res/hummer-with-screwdriver-icon-vector-19696085-removebg-preview.png \
    res/hummer-with-screwdriver-icon-vector-19696085.jpg \
    res/images (1).png \
    res/images (1).png \
    res/images (1).png \
    res/img_501696.png \
    res/imprimer.png \
    res/istockphoto-952039286-170667a.jpg \
    res/left.png \
    res/log-in.png \
    res/log-out.png \
    res/menu.png \
    res/plus-circle.png \
    res/search (3).png \
    res/search (3).png \
    res/search (3).png \
    res/stat.png \
    res/translate.png \
    res/trash-2.png \
    res/truck.png \
    res/unknown-removebg-preview.png \
    res/users.png \
    res/users1.png \
    res/wallpapersden.com_synthwave-and-retrowave_2560x1080.jpg
