#include <WiFi.h>
#include <Stepper.h>


// Define number of steps per rotation:
const int stepsPerRevolution = 2048;
const char* ssid     = "Galaxy S10e30d3";
const char* password = "shum1402";

bool down = false;

WiFiServer server(80);
Stepper myStepper = Stepper(stepsPerRevolution, 0, 2, 1, 3);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

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
    Serial.println("WiFi connected.");
    Serial.println("IP address: "); //192.168.22.194
    Serial.println(WiFi.localIP());
    
    server.begin();

    myStepper.setSpeed(15);

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    Serial.println(down);
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor

        String currentLine = String(c);
        Serial.println(currentLine);
        if (currentLine == "H" && down == false) {
          Serial.println("It works!!!");
          // Step one revolution in one direction:
          Serial.println("clockwise");
          myStepper.step(5*stepsPerRevolution);
          down = true;
        }
        if (currentLine == "L" && down == true) {
          Serial.println("It works!!!");
          // Step one revolution in one direction:
          Serial.println("Anti-clockwise");
          myStepper.step(-5*+stepsPerRevolution);
          down = false;
        }
      }
    }
    
  }
}
