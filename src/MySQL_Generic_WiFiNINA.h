/****************************************************************************************************************************
  MySQL_Generic_WiFiNINA.h
  
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, WT32_ETH01, Teensy, Portenta_H7, etc. boards 
  using W5x00, ENC28J60, LAM8742A Ethernet, WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi, Portenta Ethernet/WiFi

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
  Version: 1.5.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/08/2020 Initial coding/porting to support nRF52, SAM DUE and SAMD21/SAMD51 boards using W5x00 Ethernet
                                  (Ethernet, EthernetLarge, Ethernet2, Ethernet3 library), WiFiNINA and ESP8266/ESP32-AT shields
  1.0.1   K Hoang      18/08/2020 Add support to Ethernet ENC28J60. Fix bug, optimize code.
  1.0.2   K Hoang      20/08/2020 Fix crashing bug when timeout. Make code more error-proof. Drop support to ESP8266_AT_Webserver.
  1.0.3   K Hoang      02/10/2020 Add support to Ethernet ENC28J60 using new EthernetENC library.
  1.1.0   K Hoang      08/06/2021 Add support to RP2040-based boards such as Nano_RP2040_Connect, RASPBERRY_PI_PICO. etc.
  1.2.0   K Hoang      20/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720A)
  1.3.0   K Hoang      30/08/2021 Add support to Teensy 4.1 using NativeEthernet
  1.3.1   K Hoang      31/08/2021 Remove unnecessary SPI-bus code in NativeEthernet examples
  1.4.0   K Hoang      05/09/2021 Add support to Teensy 4.1 using QNEthernet
  1.5.0   K Hoang      17/09/2021 Add support to Portenta_H7, using either WiFi or Vision-shield Ethernet
 **********************************************************************************************************************************/

#ifndef MYSQL_GENERIC_WIFININA_H
#define MYSQL_GENERIC_WIFININA_H

#if (ESP8266 || ESP32)
  #error This code is not intended to run on the ESP8266/ESP32 platform! Please check your Tools->Board setting
#endif

#if (USING_WIFININA_GENERIC)
  #warning Using WiFiNINA_Generic Library
  #include "WiFiNINA_Generic.h"
  #include "WiFiClient_Generic.h"
  WiFiClient client;              // Use this for WiFi instead of EthernetClient
#elif (USING_WIFININA)
  #warning Using WiFiNINA Library
  #include "WiFiNINA.h"
  #include "WiFiClient.h"
  WiFiClient client;              // Use this for WiFi instead of EthernetClient
#else
  #error Must pick a Library
#endif

#include <MySQL_Generic_Connection.h>
#include <MySQL_Generic_Query.h>


#endif      //MYSQL_GENERIC_WIFININA_H
