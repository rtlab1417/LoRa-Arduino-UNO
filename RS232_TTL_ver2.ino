/* Transmit data from RS232 - simulate sensory readings
 * 
 * Description:
 * Node 1 -> transmit data on pre-defined interval time
 * Node 2 -> receive data
 * 
 * Node 1 -> apply all the code here
 * Node 2 -> mask the content of interval function, tickerCount()
 * 
 * References:
 * https://www.arduino.cc/reference/en/language/functions/communication/serial/
 * https://github.com/sstaub/Ticker
 * 
 * Note: Ticker for ESP8266 and Arduino are not the same.
 * Ticker V4.0
 
 */

#include <SoftwareSerial.h>
#include "Ticker.h"

void tickerCount();

SoftwareSerial mySerial(2, 3); // RX, TX

int data = 10000;  // assume this is sensory data
//int time_count;   // this is the interval for transmitting

Ticker ticker(tickerCount, 3000); // change every 1000ms

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // message
  Serial.println("Serial ok");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  delay(1000);
  // Ticker
  ticker.start();
  
}


void loop() {
  
  ticker.update();
  
  // read and print on Serial Monitoring
  if (mySerial.available()>0){
    Serial.write(mySerial.read()); // print on Serial Monitoring in BIN
  }
  
  //************ tranmit from mySerial
  // option 1 -> if enter data at Serial -> use previous code. No change
  
  if (Serial.available()>0 ){
    mySerial.write(Serial.read()); // send data without conversion
        
  }

}

// Option 2 -> directly send via mySerial
// trigger by predefined interval

void tickerCount(){
  // mask interval content if node 2
  // /* mask interval content if node 2

  data += 1;  // simulate the sensory data

  String str_data = String(data);
  str_data = str_data + "\r\n";     // feed new line
  
  // convert string to char of a byte size for sending over serial comm
  char char_data[str_data.length() + 1];  
  strcpy(char_data, str_data.c_str());
  mySerial.write(char_data); // send data (char[]) in BIN
  Serial.print(char_data);  // For debugging. Show the data on Serial monitoring
 
 // */ if node 2
}
