#include <ESP8266WiFi.h>
#include "HomeAtion.h"

/* Test Auth and Server */
const char* auth = "60bf07d7758b5a2873b78733";
const char* host = "homeautomationv2.herokuapp.com";
int port = 80;


HomeAtion_Connected(){
    Serial.println("Connected to Server");
}

HomeAtion_Disconnected(){
    Serial.println("Disconnected to Server");
}


void setup()
{
    Serial.begin(115200);
    WiFi.begin("ssid", "pass");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("*");
        delay(500);
    }
    Serial.println("Connected to WiFi");

    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);

    homeAtion.config(auth, host, port);


    homeAtion.WriteHandler(N0, [](String& val){
        digitalWrite(D5, val.toInt());
    });
    
    homeAtion.WriteHandler(N1, [](String& val){
        digitalWrite(D6, val.toInt());
    });

    homeAtion.WriteHandler(N2, [](String& val){
        digitalWrite(D7, val.toInt());
    });

    homeAtion.WriteHandler(N3, [](String& val){
        digitalWrite(D8, val.toInt());
    });

    homeAtion.Write(N1, 1); 


}

void loop()
{
    homeAtion.run();
}