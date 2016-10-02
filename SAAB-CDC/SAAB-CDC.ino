/*
 BlueSaab v4.0 Beta

 A CD changer emulator for older SAAB cars with RN52 Bluetooth module by Microchip Technology Inc.
 
 Credits:

 Hardware design:           Seth Evans (http://bluesaab.blogspot.com)
 Initial code:              Seth Evans and Emil Fors
 CAN code:                  Igor Real (http://secuduino.blogspot.com)
 Information on SAAB I-Bus: Tomi Liljemark (http://pikkupossu.1g.fi/tomi/projects/i-bus/i-bus.html)
 RN52 handling:             based on code by Tim Otto
 Additions/bug fixes:       Karlis Veilands and Girts Linde
*/


#include <Arduino.h>
#include "CDC.h"
#include "RN52handler.h"
#include "Timer.h"

CDChandler CDC;
Timer time;

int freeRam ()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
    Serial.begin(9600);
    Serial.println(F("\"BlueSaab\""));
    Serial.print(F("Free SRAM: "));
    Serial.print(freeRam());
    Serial.println(F(" bytes"));
    Serial.println(F("Software version: v4.0 Beta"));
    BT.initialize();
    Serial.println(F(""));
    Serial.println(F("V - Go into Discoverable Mode"));
    Serial.println(F("I - Go into non-Discoverable but Connectable Mode"));
    Serial.println(F("C - Reconnect to Last Known Device"));
    Serial.println(F("D - Disconnect from Current Device"));
    Serial.println(F("P - Play/Pause Current Track"));
    Serial.println(F("N - Skip to Next Track"));
    Serial.println(F("R - Previous Track/Beginning of Track"));
    Serial.println(F("A - Invoke Voice Assistant"));
    Serial.println(F("B - Reboot the ATMega"));
    Serial.println(F("U - Turn RN52 Volume Up"));
    Serial.println(F("O - Turn RN52 Volume Down"));
    Serial.println(F("M - Turn RN52 Volume to Max"));
    CDC.openCanBus();
}

void loop() {
    time.update();
    CDC.handleCdcStatus();
    BT.update();
    BT.monitor_serial_input();
}
