#pragma once
#include <Client.h>

#define HomeAtion_Disconnected() void HomeAtionDisconnected()
#define HomeAtion_Connected() void HomeAtionConnected()


#define N0 0
#define N1 1
#define N2 2
#define N3 3
#define N4 4
#define N5 5
#define N6 6
#define N7 7
#define N8 8
#define N9 9

HomeAtion_Connected() __attribute__((weak));
HomeAtion_Disconnected() __attribute__((weak));

typedef void (*HandlerType)(String&);

static HandlerType HomeAtionHandlers[]  = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static String States[10]; 


class HomeAtion
{
    WiFiClient client;
    
    const char *host;
    const char *auth;
    uint16_t port;
    int error = 0;
    enum State
    {
        CONNECTED,
        CONNECTING,
        DISCONNECTED
    };
    State state = CONNECTING;

    bool callServer(const String &method)
    {
        if (!client.connect(host, port))
        {
            return false;
        }

        client.print(method + " HTTP/1.0\r\n" + "Host: " + host + "\r\n" + "Connection: keep-alive\r\n" + "\r\n");

        
        uint32_t timeout = millis();
        while (client.connected() && !client.available())
        {
            if (millis() - timeout > 10000L)
            {
                return false;
            }
            delay(10);
        }


        int contentLength = -1;
        
        while (client.available())
        {
            String line = client.readStringUntil('\n');
            line.trim();
            line.toLowerCase();
            if (line.startsWith("content-length:"))
            {
                contentLength = line.substring(line.lastIndexOf(':') + 1).toInt();
            }
            else if (line.startsWith("error")){
                if (error==0) Serial.println(line.substring(line.lastIndexOf(':') + 1));
                error=1;
                return false;

            }else if (line.startsWith("np")){
                
                int pin = line.substring(2, line.lastIndexOf(':')).toInt();
                String value = line.substring(line.lastIndexOf(':') + 1);
                
                if (States[pin] != value){
                    HandlerType call = HomeAtionHandlers[pin];
                    if (call){
                        call(value);
                    }
                    States[pin] = value;
                }
            }
            else if (line.length() == 0)
            {
                break;
            }
            
        }
        
        client.stop();
        return true;
    }

public:


    void config(const char* auth, const char *host, uint16_t port = 80)
    {
        this->host = host;
        this->port = port;
        this->auth = auth;
    }

    void WriteHandler(int pin, HandlerType callback){
        HomeAtionHandlers[pin] = callback;
    }
    void Write(int pin, String val){
        
        if(!callServer(String("GET /") + auth + "/setPin/N" + pin + "?value=" + val)){
            Serial.println("Write Failed");
        } 
            
    }

    void Write(int pin, int val){
        
        if(!callServer(String("GET /") + auth + "/setPin/N" + pin + "?value=" + val)){
            Serial.println("Write Failed");
        } 
            
    }

    

    void run()
    {
        
        if (callServer(String("GET /") + auth + "/getAll"))
        {
            if (state != CONNECTED)
            {
            
                state = CONNECTED;
                HomeAtionConnected();
            }
            
        }
        else
        {
            if (state != DISCONNECTED && state != CONNECTING)
            {
                state = DISCONNECTED;
                HomeAtionDisconnected();
            }
        
        }
        // Serial.printf("Status : %d", state);
    }
    
};

HomeAtion homeAtion;