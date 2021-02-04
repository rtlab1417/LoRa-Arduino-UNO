/* Reading from MAX232 to TTL module
 * ***********************************************************************************************
 * 
 * Connection:
 * Node 1 == LoRa (E90-DTU)RS232 <---> MAX232 Module <--TTL pin --> Arduino  ==> load this .ino
 *           Tx - Pin 2  <--> Pin 3 - Rx   |          Vcc - 5VDC
 *           Rx - Pin 3  <--> Pin 2 - Tx   |          GnD - Gnd
 *           Gnd - Pin 5 <--> Pin 5 - Gnd  |          Tx  - Tx     
 *                                                    Rx  - Rx
 *                                                    
 * Node 2 == LoRa (E90-DTU) RS232  <--> RS232 to USB connecting to PC
 *           Use any serial communication app to receive and transmit data
 *        
 *************************************************************************************************
 * The idea:
 * Communication between Node 1 and Node 2 will be completed using LoRa (wireless)
 * 
 * *********************************************************************************************
 * Attempt 1: read/write using RS232 to TTL converter
 * RS232 to TTL Converter <-> MAX232 to uart module <-> Arduino
 * https://www.youtube.com/watch?v=RRxyIobPQ8M&feature=youtu.be
 * trying on serial monitoring, select one of the options:
 *    No line ending, Newline, Carriage return, Both NL & CR
 *    check out the difference in another terminal
 *    on serial terminal: add in 
 *           CR (character : \r)  --> ex: sending\r\n
 *           LF (character : \n,)
 * Working 
 ************************************************************************************************
 *
 * Attempt 2: Apply 1:1 Lora Unit communication via RS232 port
 * Unit 1 - Lora Unit E90-DTU(900SL30) <-> MAX232 module <-> Arduino <-> serial monitoring 
 * Unit 2 - Lora Unit E90-DTU(900SL30) <-> RS232 to TTL <-> serial terminal
 * Working.
 * 
 * ***********************************************************************************************
 * Attempt 3: Testing RS232 for Option 1 - transmit only, Option 2 - receive only, Option 3: full duplex mode.
 * Option 1 - If MCU-Arduino only transmit - We could remove the connection of Pin-02 of DB9 (which is Tx of the LoRa unit)
 *          - working
 * Option 2 - Wise-versa - if MCU-Arduino only receiving data, we could remove Pin-03 of DB9 (which is Rx of the LoRa unit)
 *          - Working
 * Option 3 - If MCU-Arduino is transmitting (very long texts), 
 * 
 * ****************************************************************************************************
 * This example code is in the public domain. <SoftwareSerial.h>
 * Reference:
 * https://forum.arduino.cc/index.php?topic=455333.0
 
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  Serial.println("Serial ok\r");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //mySerial.println("Hello, world?");
}

void loop() // run over and over
{
 
  // receive from mySerial and post on serial monitoring
  // data flow: mySerial (read) -> Serial (write) -> PC (read)
  // mySerial.available() returns the number of bytes (characters) available for reading from mySerial port
  if (mySerial.available()>0){
    Serial.write(mySerial.read()); // send data without conversion
    //Serial.println(mySerial.read()); // Conversion. write ASCII data with carriage return (\r) and newline (\n)
  }
  
  // tranmit to mySerial (by reading from serial monitoring)
  // data flow: PC (write) -> Serial (read) -> mySerial (write)
  // Serial.available() returns the number of bytes (characters) available for reading from Serial port
  if (Serial.available()>0){
    mySerial.write(Serial.read()); // send data without conversion
    //mySerial.println(Serial.read(),HEX); // Conversion. write ASCII data with carriage return (\r) and newline (\n)
  }
}
