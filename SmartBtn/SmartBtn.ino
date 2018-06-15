
/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//#include <Adafruit_LIS3DH.h>
#include "user_interface.h"
#include "hw_config.h"
#include <WiFiUdp.h>

#include <EEPROM.h>

#include <FirebaseArduino.h>

#include <ArduinoJson.h>

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on


const int INCOMING_PACKET_SIZE = 2048;
char incomingPacket[INCOMING_PACKET_SIZE];
char replyOK[] = "OK";
char replyFAIL[] = "FAIL";

#define FIREBASE_PROJECT_URL  "FB_HOST_URL"
#define FIREBASE_AUTH_KEY  "FB_AUTH_KEY"
#define FIREBASE_USER_UID  "USER_UID"
#define FIREBASE_LISTEN_URL  "LISTEN_URL"
#define FIREBASE_LISTEN_NODE  "LISTEN_NODE"
#define FIREBASE_DEVICE_LED_NUMBER "LED_NUM"
#define FIREBASE_CONN_STATE_SUCCESS  0
#define FIREBASE_CONN_STATE_FAILED  -1

// PIN DEFINE
#define BUILTIN_LED 2     // ESP-12E module's onboard LED, used as status indicator
#define BUILTIN_LED_OFF() digitalWrite(BUILTIN_LED, HIGH)
#define BUILTIN_LED_ON()  digitalWrite(BUILTIN_LED, LOW)

#define CONTROL_AUTOMATICALLY 1
#define CONTROL_MANUALLY 2

class FirebaseConfig{

  private:
  const char* mFirebase_host;
  const char* mFirebase_auth;
  int CONN_STATE;

  public:
  FirebaseConfig(){
    
  }
  
  FirebaseConfig(const char* firebase_host, const char* firebase_auth){
    mFirebase_host = firebase_host;
    mFirebase_auth = firebase_auth;
    CONN_STATE = FIREBASE_CONN_STATE_FAILED;
  }

  
  const char* getFirebaseHost(){
    return mFirebase_host;
  }
  
  const char* getFirebaseAuth(){
    return mFirebase_auth;
  }

  void setConnState(int state){
    CONN_STATE = state;
  }

  int getConnState(){
    return CONN_STATE;
  }
};

FirebaseConfig * fbConfig = NULL;

void readEEPROM(){

  EEPROM.begin(INCOMING_PACKET_SIZE);
  Serial.print("Reading from EEPROM\n");
  char isAvail = EEPROM.read(0);
  char * data = NULL;
  if ('Y' == isAvail){
    Serial.println(isAvail);
    data = (char*)malloc(sizeof(char)+(INCOMING_PACKET_SIZE));
    char c;
    int j = 1;
    int i = 0;
    while( ( c = EEPROM.read(j)) != '\0'){
      data[i] = c;
      i++;
      j++;
    }
    Serial.println(data);
    if (NULL != data){
      data[i] = '}';
      Serial.printf("Data is %s\n", data);
  
      StaticJsonBuffer<INCOMING_PACKET_SIZE> jsonBuffer;
    
      JsonObject& root = jsonBuffer.parseObject(data);
    
      
      fbConfig = new FirebaseConfig(root[FIREBASE_PROJECT_URL], root[FIREBASE_AUTH_KEY]);
    
      //const char * listenUrl = root[FIREBASE_LISTEN_URL];
      //thisDeviceConfig = new SmartDeviceConfig(listenUrl); 
    } 
    
  }
  
}

void clean(){
   EEPROM.begin(INCOMING_PACKET_SIZE);
    for (int i = 0; i < INCOMING_PACKET_SIZE; i++){
      EEPROM.write(i, '\0');
    }
  
    EEPROM.commit();
    EEPROM.end();
}

void setup() {

  
  
    Serial.begin(115200);
    
    // setup WiFi
    // no need to config SSID and password
    // turn on Auto Connect

   
   
   readEEPROM();
   
   
    if (NULL == fbConfig){
          configWifi();
    }
    else{
      WiFi.mode(WIFI_STA);   
      WiFi.setAutoConnect(true);   
      delay(1000);    
      Firebase.begin(fbConfig->getFirebaseHost(), fbConfig->getFirebaseAuth());
      if(Firebase.failed()){
        Serial.println("Firebase auth failed");
        Serial.println(Firebase.error());
      }
      else{
        Serial.println("Success");  
        
      }
        
      
    }
     
}

void configWifi(){

  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(false);

  // start WiFi connecting
          int cnt = 0;
          while (WiFi.status() != WL_CONNECTED) {
              // onboard LED flash twice quickly
              // UART output "..." 
              // ESP8266 is trying to connect to a known WiFi
              
              delay(100);
              
              delay(50);
              Serial.print(".");
       
              // if no connection available after timeout
              if (cnt++ >= 10) {
                  Serial.println("");
                  WiFi.beginSmartConfig();
                  while (1) {
                      // onboard LED flash slowly
                      // UART output "|||" 
                      // ESP8266 is in smartconfig loop
                      // use app to finish the smartconfig
                      
                      delay(900);
                      
                      if (WiFi.smartConfigDone()) {
                          Serial.println();
                          Serial.println(F("[WIFI] SmartConfig: Success"));
      
                            Serial.print("ssid:");
                            Serial.println(WiFi.SSID());
                            Serial.print("password:");
                            Serial.println(WiFi.psk());
        
                          break;
                      }
                      Serial.print(F("|"));
                  }
              }
              BUILTIN_LED_OFF();
          }
       
          Serial.println("");
          Serial.println(F("WiFi connected"));  
          Serial.print(F("IP address: "));
          Serial.println(WiFi.localIP());
       
          WiFi.printDiag(Serial);
       
          Serial.print(F("RSSI: "));
          Serial.println(WiFi.RSSI());
          Serial.print(F("BSSID: "));
          Serial.println(WiFi.BSSIDstr());
      
          Udp.begin(localUdpPort);
          Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

          
}

void loop(){
  if (NULL == fbConfig){
    listen_udp();
  }
  else{
      //read from firebase
      if (WiFi.status() != WL_CONNECTED){
        Serial.println("Wifi is not connected");
        delay(200);
      }
      else{
          /*FirebaseObject curObj = Firebase.get(thisDeviceConfig->getListenUrl());
          if (Firebase.success()){
            Serial.println("Success");
            Serial.println(thisDeviceConfig->getListenNode());
          }*/
      }
  }
    
}

void listen_udp(){
  

  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, INCOMING_PACKET_SIZE);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }

    EEPROM.begin(INCOMING_PACKET_SIZE);
    for (int i = 0; i < INCOMING_PACKET_SIZE; i++){
      EEPROM.write(i, '\0');
    }
  
    EEPROM.commit();
    EEPROM.end();
    
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    EEPROM.begin(INCOMING_PACKET_SIZE);
    Serial.printf("data is %s\n",incomingPacket);
    int i = 0;
    int j = 0;
    EEPROM.write(0, 'Y');
    for (i = 1; i < len; i++, j++){
      EEPROM.write(i, incomingPacket[j]);      
    }
    delay(200);
    EEPROM.commit();
    EEPROM.end();
      
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    
    StaticJsonBuffer<INCOMING_PACKET_SIZE> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(incomingPacket);

    if (!root.success()){
      
       // send back a reply, to the IP address and port we got the packet from
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(replyFAIL);
      Udp.endPacket();
  
      
    }
    else{
      // send back a reply, to the IP address and port we got the packet from
      fbConfig = new FirebaseConfig(root[FIREBASE_PROJECT_URL], root[FIREBASE_AUTH_KEY]);

        
      
       // send back a reply, to the IP address and port we got the packet from
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(replyOK);
      Udp.endPacket();

      Firebase.begin(fbConfig->getFirebaseHost(), fbConfig->getFirebaseAuth());
      if(Firebase.failed()){
        Serial.println("Firebase auth failed");
        Serial.println(Firebase.error());
      }
      else{
        Serial.println("Success");  
        
      }
      Udp.stop(); 
      
     
      WiFi.setAutoConnect(true);
      
    }

    Serial.printf("\n");   
    
  }
  delay(500);
}


 
