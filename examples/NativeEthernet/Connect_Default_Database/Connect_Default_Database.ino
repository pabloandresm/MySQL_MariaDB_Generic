/*********************************************************************************************************************************
  Connect_Default_Database.ino
      
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
  MySQL Connector/Arduino Example : connect with default database

  This example demonstrates how to connect to a MySQL server and specifying
  the default database when connecting. 

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Connect a USB cable to your Arduino
  4) Select the correct board and port
  5) Compile and upload the sketch to your Arduino
  6) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  If you do not see messages indicating you have a connection, refer to the
  manual for troubleshooting tips. The most common issues are the server is
  not accessible from the network or the user name and password is incorrect.

  Note: The MAC address can be anything so long as it is unique on your network.

  Created by: Dr. Charles A. Bell
*/

#include "defines.h"

#include <MySQL_Generic.h>

// Select the static Local IP address according to your local network
IPAddress ip(192, 168, 2, 222);

IPAddress server_addr(192, 168, 2, 112);
uint16_t server_port = 5698;    //3306;

char user[]             = "invited-guest";              // MySQL user login username
char password[]         = "the-invited-guest";          // MySQL user login password

char default_database[]       = "world";

MySQL_Connection conn((Client *)&client);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  MYSQL_DISPLAY3("\nStarting Connect_Default_Database on", BOARD_NAME, ", with", SHIELD_TYPE);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);

  MYSQL_LOGERROR(F("========================================="));
  MYSQL_LOGERROR(F("Default SPI pinout:"));
  MYSQL_LOGERROR1(F("MOSI:"), MOSI);
  MYSQL_LOGERROR1(F("MISO:"), MISO);
  MYSQL_LOGERROR1(F("SCK:"),  SCK);
  MYSQL_LOGERROR1(F("SS:"),   SS);
  MYSQL_LOGERROR(F("========================================="));

  // use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif

  MYSQL_LOGERROR3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
 
  Ethernet.init (USE_THIS_SS_PIN);

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  // Just info to know how to connect correctly
  MYSQL_LOGERROR(F("========================================="));
  MYSQL_LOGERROR(F("Currently Used SPI pinout:"));
  MYSQL_LOGERROR1(F("MOSI:"), MOSI);
  MYSQL_LOGERROR1(F("MISO:"), MISO);
  MYSQL_LOGERROR1(F("SCK:"),  SCK);
  MYSQL_LOGERROR1(F("SS:"),   SS);
  MYSQL_LOGERROR(F("========================================="));

  MYSQL_DISPLAY1("Using mac index =", index);
  MYSQL_DISPLAY1("Connected! IP address:", Ethernet.localIP());

  MYSQL_DISPLAY3("Connecting to SQL Server @", server_addr, ", Port =", server_port);
  MYSQL_DISPLAY5("User =", user, ", PW =", password, ", DB =", default_database);
}

void loop()
{
  MYSQL_DISPLAY("Connecting...");
  
  //if (conn.connect(server_addr, server_port, user, password))
  if (conn.connectNonBlocking(server_addr, server_port, user, password) != RESULT_FAIL)
  {
    MYSQL_DISPLAY("Closing connection...");
    conn.close();                     // close the connection
  } 
  else 
  {
    MYSQL_DISPLAY("\nConnect failed. Trying again on next iteration.");
  }

  MYSQL_DISPLAY("\nSleeping...");
  MYSQL_DISPLAY("================================================");
 
  delay(60000);
}