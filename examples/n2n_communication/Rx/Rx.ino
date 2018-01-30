#include <Arduino.h>
#include <cc1101.h>
#include <ccpacket.h>

#define CC1101Interrupt 0
#define CC1101_GDO0 2

#define PIN_LED1 A1
#define PIN_LED2 A2
#define PIN_HGM 5
#define PIN_LNA 6
#define PIN_PA 7

// created radio 
CC1101 radio;

byte syncWord[2] = {199, 10};
bool packetWaiting;

void messageReceived() {
    packetWaiting = true;
}

int counter=0;

void setup() {
    Serial.begin(115200);

    // setup pin directions
    pinMode(PIN_LED1,OUTPUT);
    pinMode(PIN_LED2,OUTPUT);
    pinMode(PIN_HGM,OUTPUT);
    pinMode(PIN_LNA,OUTPUT);
    pinMode(PIN_PA,OUTPUT);

    // initialized and configured radio
    radio.init();
    radio.setSyncWord(syncWord);
    radio.setCarrierFreq(CFREQ_868);
    radio.disableAddressCheck();
    radio.setTxPowerAmp(PA_LongDistance);

    // attached interrupt
    attachInterrupt(CC1101Interrupt, messageReceived, FALLING);
}

// See: http://www.ti.com/lit/an/swra114d/swra114d.pdf
int rssi(char raw) {
    uint8_t rssi_dec;
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
    digitalWrite(PIN_LNA,HIGH);
    digitalWrite(PIN_PA,LOW);

    // if there is any data from radio
    if (packetWaiting) {
        detachInterrupt(CC1101Interrupt);
        packetWaiting = false;
        CCPACKET packet;
        // recieving available data
        if (radio.receiveData(&packet) > 0) {
            //Serial.println(F("Received packet..."));
            if (!packet.crc_ok) {
                //Serial.println(F("crc not ok"));
            }
            // parsing and printing data
            if (packet.crc_ok && packet.length > 0) {
                Serial.print("@{\"deviceID\":");
                Serial.print(packet.data[0],DEC);
                Serial.print(",\"temperature\":");
                Serial.print(packet.data[1],DEC);
                Serial.print(",\"humidity\":");
                Serial.print(packet.data[2],DEC);
                Serial.print("}\r\n");

                digitalWrite(PIN_LED1,HIGH);
                delay(100);
                digitalWrite(PIN_LED1,LOW);
                
                digitalWrite(PIN_LED2,HIGH);
                delay(100);
                digitalWrite(PIN_LED2,LOW);
            }
        }
        attachInterrupt(CC1101Interrupt, messageReceived, FALLING);
    }
}
