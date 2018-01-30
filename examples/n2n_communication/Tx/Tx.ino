#include <Arduino.h>
#include <cc1101.h>
#include <ccpacket.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"

#define PIN_LED1 A1
#define PIN_LED2 A2
#define PIN_HGM 5
#define PIN_LNA 6
#define PIN_PA 7

#define DEVICE_ID 100 

#define CC1101Interrupt 0 // Pin 2
#define CC1101_GDO0 2

// created hdc1080
ClosedCube_HDC1080 hdc1080;

// created radio
CC1101 radio;

byte syncWord[2] = {199, 10};
bool packetWaiting;

int counter=0;

void setup() {
    Serial.begin(115200);

    // configured pin directions
    pinMode(PIN_LED1,OUTPUT);
    pinMode(PIN_LED2,OUTPUT);
    pinMode(PIN_HGM,OUTPUT);
    pinMode(PIN_LNA,OUTPUT);
    pinMode(PIN_PA,OUTPUT);

    // Initialized and configured hdc1080
    hdc1080.begin(0x40);
    hdc1080.setResolution(HDC1080_RESOLUTION_11BIT, HDC1080_RESOLUTION_11BIT);

    // Initialized and configured hdc1080
    radio.init();
    radio.setSyncWord(syncWord);
    radio.setCarrierFreq(CFREQ_868);
    radio.disableAddressCheck();
    radio.setTxPowerAmp(PA_LongDistance);

    // cc1101 information
    Serial.print(F("CC1101_PARTNUM "));
    Serial.println(radio.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
    Serial.print(F("CC1101_VERSION "));
    Serial.println(radio.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
    Serial.print(F("CC1101_MARCSTATE "));
    Serial.println(radio.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

    Serial.println(F("CC1101 radio initialized."));
}

// Get signal strength indicator in dBm.
// See: http://www.ti.com/lit/an/swra114d/swra114d.pdf
int rssi(char raw) {
    uint8_t rssi_dec;
    // TODO: This rssi_offset is dependent on baud and MHz; this is for 38.4kbps and 868 MHz.
    uint8_t rssi_offset = 74;
    rssi_dec = (uint8_t) raw;
    if (rssi_dec >= 128)
        return ((int)( rssi_dec - 256) / 2) - rssi_offset;
    else
        return (rssi_dec / 2) - rssi_offset;
}

// Get link quality indicator.
int lqi(char raw) {
    return 0x3F - raw;
}

void loop() {

  // configured HGM, LNA, PA
  digitalWrite(PIN_HGM,HIGH);
  digitalWrite(PIN_LNA,LOW);
  digitalWrite(PIN_PA,HIGH);

  // packet created and added measured sensor datas.  
  CCPACKET packet;
  packet.length=4;
  packet.data[0] = DEVICE_ID;
  packet.data[1] = hdc1080.readTemperature();
  packet.data[2] = hdc1080.readHumidity();
  packet.data[3] = '\0' ;

  // sending packet
  if(radio.sendData(packet))
  {
    Serial.println(F("Sent packet..."));
    
    digitalWrite(PIN_LED1,HIGH);
    delay(100);
    digitalWrite(PIN_LED1,LOW);
    
    digitalWrite(PIN_LED2,HIGH);
    delay(100);
    digitalWrite(PIN_LED2,LOW);
  }

  // added delay
  delay(1000);
}
