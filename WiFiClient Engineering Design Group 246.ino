#include <WiFi.h>

// defines pin numbers for the ultrasonic sensor
const int trigPin = 0;
const int echoPin = 1;

// defines variables
long duration;
int distance;

//Necessary information regarding Wifi connection
const char* ssid     = "Galaxy S10e30d3";
const char* password = "shum1402";

const char* host = "192.168.191.194";

String hostString = String(host);

void setup()
{
    Serial.begin(115200);
    delay(10);

    //Initialize Ultrasonic proximity sensor's echo and trigger pins
    pinMode(trigPin, OUTPUT);   // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);    // Sets the echoPin as an Input

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    WiFi.setTxPower(WIFI_POWER_8_5dBm);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance= duration*0.034/2;

    // Prints the distance on the Serial Monitor
    Serial.println(distance);
    delay(500);
    
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    if (distance <= 10) {
      client.print("H");
      Serial.println("Pin going down");
    } else if (distance > 10) {
      client.print("L");
      Serial.println("Pin going up");
    }
    delay(1000);
}
