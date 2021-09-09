// ========================================================================================
//      Meine Welt in meinem Kopf
// ========================================================================================
// Projekt:       Sensor Daten über Smart Port versenden mit dem Arduino
// Author:        Johannes P. Langner
// Controller:    Arduino UNO / Mini
// Receiver:      FrSky RX4R
// Description:   Einen Wert über Smart Port versenden und auf dem OpenTX Fernsteuerung 
//                den Wert anzeigen.
//                Code stammt aus den vorliegenden Beispiel 'CustomSesnor' und wurde 
//                um einen Zähler erweitert.
// Stand:         09.09.2021
// ========================================================================================

#include <SPort.h>

// ========================================================================================
// setup SmartPort
SPortHub hub(0x12, 3);                    // Hardware ID 0x12, Software serial pin 3
CustomSPortSensor sensor(getSensorData);  // Sensor mit einer callback Funktion 

// ========================================================================================
// Simuliert die aenderung.
int mSendingValue = 0;
int mCurrentMillis;

// ========================================================================================
void setup() {
  hub.registerSensor(sensor);             // Registriert den Sensor an den HUB.
  hub.begin();                           
}

// ========================================================================================
void loop() {
  hub.handle();                           // abruf neuer Daten

  int current = millis();
  if(mCurrentMillis - current < 1000) {
     return;
  }
  mCurrentMillis = current;
  mSendingValue++;   
}

// ========================================================================================
// Get the sensor value result to SPortData
sportData getSensorData(CustomSPortSensor* sensor) {
  sportData data; 
  data.applicationId = 0x5900;            // Legt die Sensor ID fest 
                                          // Wenn 0 gesetzt ist, dann wird dieser übersprungen.
  data.value = mSendingValue;             // Set the sensor value 
  return data;
}
