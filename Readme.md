
# IotServer

This project is based on NodeJs, MongoDb and ESP266




## Installation 

This project can be used through Arduino Ide but this project specifically uses makeEspArduino and following commands are for installing makeEspArduino and ESP8266 Arduino Core.

```bash 
  python3 build/get.py install
```
    
## Building and Flashing with makeEspArduino 

This project can be used through Arduino Ide but this project specifically uses makeEspArduino and following commands are for installing makeEspArduino and ESP8266 Arduino Core.

```make run```     - Building, Flashing and Opening Serial Monitor 

```make monitor``` - Opening Serial Monitor

```make flash```   - Flashing firmware to EspBoard

```make all```     - Build the Program

These are some Basic Commmands. You can find more commands at [makeEspArduino](https://www.github.com/animeshdhakal) github Repo.
## Usage/Examples

```c++
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
```

  
## API Reference for NodeJS Server

#### Get All UsedPins in Header

```http
  GET /${auth}/getAll
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `auth` | `string` | **Required**. Your Auth key   |

#### Set Pin Value

```http
  GET /${auth}/setPin/${Pin}?value=${value}
```

| Parameter | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `auth`    | `string` | **Required**. Your Auth key       |
| `Pin`     | `string` | **Required**. Pin starting from N0 to N9 |
| `value`   | `string` | **Required**. Value to set in the respective Pin |


  
## Authors

- [@animeshdhakal](https://www.github.com/animeshdhakal)

  