#include "arduino.h"
#include <QDebug>
arduino::arduino()
{

  data = "";
  arduino_port_name="";
  arduino_is_available=false;
  serial= new QSerialPort;

}

int arduino::connect_arduino()
{
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
                if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id && serialPortInfo.productIdentifier()
                        == arduino_uno_product_id){
                        arduino_port_name = serialPortInfo.portName();
                        arduino_is_available = true;
                    }

            }
        }
        qDebug()<< "arduino proort name is"<<arduino_port_name << arduino_is_available;
        if(arduino_is_available){ //configuration de la communication
            // open and configure the serialport
            serial->setPortName(arduino_port_name);
            serial->open(QSerialPort::ReadWrite);
            serial->setBaudRate(QSerialPort::Baud115200);// quand je dois initialiser l'arduino de pref je mets Serial.begin(115200) debit;
            serial->setDataBits(QSerialPort::Data8);//longuer des données 8bits
            serial->setParity(QSerialPort::NoParity); //1bit
            serial->setStopBits(QSerialPort::OneStop); //nbr de bit de stop 1
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;

    }
        return 1;
}

int arduino::close_arduino()
{if (serial->isOpen()){serial->close(); return 0;}
    return 0;

}


QByteArray arduino::read_from_arduino()
{
    if (serial->isReadable())
    {
        data=serial->readAll();
        return data;
    }
}

QSerialPort *arduino::getserial() //
{
    return serial;
}

QString arduino::getarduino_port_name()
{
    return arduino_port_name;
}

void  arduino::write_arduino(QByteArray d)
{
    if(serial->isReadable()){serial->write(d);
    }
    else {qDebug() <<"couldnt open";}


}
