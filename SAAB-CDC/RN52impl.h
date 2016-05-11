#ifndef RN52impl_H
#define RN52impl_H

#include "Arduino.h"
#include "RN52driver.h"
#include "SoftwareSerial.h"

/**
 * Atmel 328 pin definitions:
 */

const int BT_STATUS_PIN = 3;    // RN52 GPIO2 pin for reading current status of the module
const int BT_CMD_PIN = 4;       // RN52 GPIO9 pin for enabling command mode
const int BT_FACT_RST_PIN = A0; // RN52 factory reset pin GPIO4
const int BT_PWREN_PIN = 9;     // RN52 Power enable pin
const int UART_TX_PIN = 5;      // UART Tx
const int UART_RX_PIN = 6;      // UART Rx

bool playing = true;
bool bt_iap = false;
bool bt_spp = false;
bool bt_a2dp = false;
bool bt_hfp = false;

// extend the RN52driver to implement callbacks and hardware interface
class RN52impl : public RN52::RN52driver {
    // called by RN52lib when the connected Bluetooth devices uses a profile
    void onProfileChange(BtProfile profile, bool connected);
    
    SoftwareSerial softSerial =  SoftwareSerial(UART_RX_PIN, UART_TX_PIN);
    
public:
    // this is used by RN52lib to send data to the RN52 module
    // the implementation of this method needs to write to the
    // connected serial port
    void toUART(const char* c, int len);
    // this method is called by RN52lib when data arrives via
    // the SPP profile
    void fromSPP(const char* c, int len);
    // this method is called by RN52lib whenever it needs to
    // switch between SPP and command mode
    void setMode(Mode mode);
    // GPIO2 of RN52 is toggled on state change, eg. a Bluetooth
    // devices connects
    void onGPIO2();
    
    void initializeAtmelPins();
    void bt_play();
    void bt_pause();
    void bt_prev();
    void bt_next();
    void bt_visible();
    void bt_invisible();
    void bt_reconnect();
    void bt_disconnect();
};

#endif
