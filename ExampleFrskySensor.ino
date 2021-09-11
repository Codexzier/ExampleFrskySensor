// ========================================================================================
//      Meine Welt in meinem Kopf
// ========================================================================================
// Projekt:       Sensor Daten über Smart Port versenden mit dem Arduino
// Author:        Johannes P. Langner
// Controller:    Arduino UNO / Mini
// Receiver:      FrSky RX4R
// Sensor:        TMP102
// Description:   Der Temperatur Wert wird über den Smart Port versendet und auf der 
//                Fernsteuerung mit OpenTX und LUA Script unterstützung Empfangen.
//                Das dazugehörige Script rechnet den Rohwert in ein Lesbaren 
//                Temperatur Wert.
// Stand:         11.09.2021
// ========================================================================================

#include <SPort.h>
#include <Wire.h>

// ========================================================================================
// setup SmartPort
SPortHub hub(0x12, 3);                    // Hardware ID 0x12, Software serial pin 3
CustomSPortSensor sensor(getSensorData);  // Sensor mit einer callback Funktion 

// ========================================================================================
// temperatur sensor
#define TMP102_ADD 0x48

// ========================================================================================
void setup() {
  Serial.begin(115200);
  Wire.begin();
  hub.registerSensor(sensor);             // Registriert den Sensor an den HUB.
  hub.begin();                           
}

// ========================================================================================
void loop() {
  hub.handle();                           // abruf neuer Daten
}

// ========================================================================================
// Get the sensor value result to SPortData
sportData getSensorData(CustomSPortSensor* sensor) {
  sportData data; 
  data.applicationId = 0x5900;            // Legt die Sensor ID fest 
                                          // Wenn 0 gesetzt ist, dann wird dieser übersprungen.
  int raw = getTemperatureValue();             // Set the sensor value 

  float result = raw * 0.0625;
  Serial.print("Temperatur: ");
  Serial.println(result, DEC);

  data.value = raw;
  return data;
}

int getTemperatureValue() {
  Wire.beginTransmission(TMP102_ADD);
  Wire.write(0x00);
  delay(100);
  Wire.endTransmission();

  Wire.requestFrom(TMP102_ADD, 2);
  while(Wire.available() < 2) { }

  return ((Wire.read() << 8) | Wire.read()) >> 4;
}
