#include <WiFi.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HttpClient.h>
#include <Bridge.h>
#include <Ethernet.h>
#include "HX711.h"

#define ONE_WIRE_BUS 2
#define O1 10

HX711 scale(A1,A0);



OneWire oneWire(ONE_WIRE_BUS);




//Pass address of our oneWire instance to Dallas Temperature.
DallasTemperature sensors(&oneWire);
int estado;
int estado_teste=0;
float Celcius=0;
float Fahrenheit=0;


int weight = 100;
char ssid[] ="SE1718";  // the name of your network
int status = WL_IDLE_STATUS;  // the Wifi radio's status

char c = 'n';
char server[] = "192.168.10.2";
//for printing data from server


float y;
float calibration_factor = -11600;

IPAddress ip(192,168,10,4);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;







void setup() {
 Serial.begin(9600);//Begin serial communication
  while (!Serial) {
    ; // wait for serial port to connect. 
  }
 
  
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 

  
 // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to open SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
   
  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();



 sensors.begin();
 
 scale.set_scale();
 scale.tare(); //Reset the scale to 0
 long zero_factor = scale.read_average(); //Get a baseline reading
 Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
 Serial.println(zero_factor);
 Serial.println("Put the chaleira men");
 digitalWrite(O1,LOW);
 pinMode(O1, OUTPUT); 
 
}

bool tr = 0;

void loop() {
  tr=chaleira(tr);
  if(chaleira(tr)) digitalWrite(O1,HIGH);
  else digitalWrite(O1,LOW);
  client.flush();
  client.stop();
}


bool chaleira(bool tr){
  
  if(tr) digitalWrite(O1,HIGH);
  else digitalWrite(O1,LOW);
  sensors.requestTemperatures();//Send the command to get temperatures
  //delay(1000); 
  Celcius=sensors.getTempCByIndex(0);// Get and save sensor value
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 

  Fahrenheit=sensors.getTempFByIndex(0);// Get and save sensor value

 
 Serial.println("--------------------");
 Serial.print(" C  ");
 Serial.println(Celcius,2);
 Serial.print(" F  ");
 Serial.println(Fahrenheit,2);
  

  
  
 Serial.println("--------------------");
 scale.set_scale(calibration_factor); //Adjust to this calibration factor

 Serial.print("Reading: ");
 y = map(scale.get_units(),18,34,0,450);
 Serial.print(y);
 Serial.println(" g");
 Serial.println("--------------------");
 
  // if you get a connection, report back via serial:
  delay(1000);
  if(tr) digitalWrite(O1,HIGH);
  else digitalWrite(O1,LOW);


  client.flush();
  client.stop();
  if (client.connect(server, 8080)) {
    
    Serial.println("connected to server");
     if(tr) digitalWrite(O1,HIGH);
     else digitalWrite(O1,LOW);
    // Make a HTTP request:
    client.println("GET /entry-point/arduino?wg_=" + String(y) + "&temp_=" + String(Celcius) + "&on_=" + c + " HTTP/1.1");
    client.println("Host: 192.168.10.2");
    client.println("Connection: close");
    client.println();
  }
    if(tr) digitalWrite(O1,HIGH);
  else digitalWrite(O1,LOW);
  delay(5000);
    if(tr) digitalWrite(O1,HIGH);
  else digitalWrite(O1,LOW);
 
  // if there are incoming bytes available
  // from the server, read them and print them:
    Serial.println(client.available());
    if(tr) digitalWrite(O1,HIGH);
    else digitalWrite(O1,LOW);
  
  while (client.available()>0) {
      if(tr) digitalWrite(O1,HIGH);
      else digitalWrite(O1,LOW);
      //Serial.println(estado_teste);

    c = client.read();
    if(c == '#') {
      while(client.available() == 0) { 
        if(tr) digitalWrite(O1,HIGH);
        else digitalWrite(O1,LOW);
        }
      // Do nothing while we wait for the next value
      // reading the second character
      c = client.read();
      if(tr) digitalWrite(O1,HIGH);
      else digitalWrite(O1,LOW);
    }
    
    if(tr) digitalWrite(O1,HIGH);
    else digitalWrite(O1,LOW);
  }

  
 
 /*if(valor == 'n'){
  //digitalWrite(O1, LOW);
  Serial.println("É um n");
 }
 else if(valor =='s'){
  //digitalWrite(O1, HIGH);
  Serial.println("É um s");
 }
    // if the server's disconnected, stop the client:
 /* if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    
  }*/
  //client.flush();
  //client.stop();
  if(tr) digitalWrite(O1,HIGH);
  else digitalWrite(O1,LOW);
  delay(5000);
  if(tr) digitalWrite(O1,HIGH);
  else digitalWrite(O1,LOW);
  
  Serial.println(c);
  if(c == 's') return 1;
  return 0;
  client.flush();
  client.stop();
}


  void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);
  
  // print your MAC address:
  byte mac[6];  
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  
  // print your subnet mask:
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);    
  Serial.print("BSSID: ");
  Serial.print(bssid[5],HEX);
  Serial.print(":");
  Serial.print(bssid[4],HEX);
  Serial.print(":");
  Serial.print(bssid[3],HEX);
  Serial.print(":");
  Serial.print(bssid[2],HEX);
  Serial.print(":");
  Serial.print(bssid[1],HEX);
  Serial.print(":");
  Serial.println(bssid[0],HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption,HEX);
}


