#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2

//Global Variables                             // and the RX line from the esp to the Arduino's pin 3
int connectionId;

//Function declearation
void sendWebPage(String); 
void closeConnection();
void sendCommand(String);

void setup()
{
  esp8266.begin(9600); // your esp's baud rate might be different
  
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);

  pinMode(8,INPUT);
  pinMode(9,OUTPUT);
  
  esp8266.print("AT+RST\r\n"); // reset module
  delay(2000);
  //sendCommand("AT+CWMODE=3"); // configure as access point and station
  
  //sendCommand("AT+CWJAP=\"IoT Server\",\"iot_server@cse\""); // set station ssid and pwd
  //sendCommand("AT+CWSAP=\"ESP8266 Relay Server\",\"esp_iot@cse\",11,3"); // set ap ssid and pwd
  
  //sendCommand("AT+CIFSR"); // get ip address
  sendCommand("AT+CIPMUX=1"); // configure for multiple connections
  sendCommand("AT+CIPSERVER=1,80"); // turn on server on port 80
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
    if(esp8266.find("+IPD,"))
    {
     delay(500); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48  
     if(esp8266.find("pin=")) // advance cursor to "pin="
     {
      int pinNumber = (esp8266.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
      pinNumber += (esp8266.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
        
      if(digitalRead(pinNumber))
      {
        sendWebPage("<html><head><title>IoT Smart Home Automation</title></head><body><center><h1>Light Off!</h1></center></body></html>");
      }
      else
      {
        sendWebPage("<html><head><title>IoT Smart Home Automation</title></head><body><center><h1>Light On!</h1></center></body></html>");
      }
      digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin 
      closeConnection();
     }
     else
     {
      sendWebPage("<html><head><title>IoT Smart Home Automation</title></head><body><center><h1>ESP8266 IoT Relay Server</h1></center></body></html>");
      closeConnection(); 
     }
    }
  }
}

void sendWebPage(String htmlData)
{
  String htmlSendCommand = "AT+CIPSEND=";
  htmlSendCommand+=connectionId;
  htmlSendCommand+=",";
  htmlSendCommand+=htmlData.length()+2;
  htmlSendCommand+="\r\n";
  esp8266.print(htmlSendCommand);
  delay(100);
  //delay(htmlSendCommand.length());
  htmlData+="\r\n";
  esp8266.print(htmlData);
  delay(htmlData.length());
}

void closeConnection()
{
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     esp8266.print(closeCommand); // close connection
     delay(closeCommand.length());
}

void sendCommand(String command)
{
  command+="\r\n";
  esp8266.print(command);
  delay(command.length());
  delay(10);
}