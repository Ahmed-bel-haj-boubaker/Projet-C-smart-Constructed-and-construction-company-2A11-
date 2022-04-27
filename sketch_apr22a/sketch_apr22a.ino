#include <dht11.h>
#include <LiquidCrystal_I2C.h>
#define DHT11PIN 2 // broche DATA -> broche 2
#define ventilateurPIN 1 // broche -> pour ventilateur
//LiquidCrystal_I2C lcd(0x27, 20, 4);

dht11 DHT11;

void setup()
{ pinMode(ventilateurPIN,OUTPUT); //règle la borne numérique numéro 2 de la carte Arduino en mode sortie
lcd.init(); // initialisation de l’afficheur
}

void loop()
{
DHT11.read(DHT11PIN);

lcd.backlight(); // active le rétro-éclairage
lcd.clear(); // effacer le contenu de l’Afficheur LCD
lcd.setCursor(0, 0); // se positionner à la première ligne
lcd.print("temperature= ");
lcd.setCursor(0,1); // se positionner à la deuxième ligne
lcd.print((float)DHT11.temperature); // Afficher la température sur l'afficheur
if ((float)DHT11.temperature >28) {
digitalWrite(ventilateurPIN,HIGH); // le ventilateur se met à tourner
} else {
digitalWrite(ventilateurPIN,LOW); // le ventilateur s'arrête
}
delay(2000);
}
