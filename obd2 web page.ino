#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FirebaseArduino.h>
#include <Ethernet.h>


//liaison firebase
#define FIREBASE_HOST "firebase project package"
#define FIREBASE_AUTH "firebase private key"

// SSID and PASSWORD for the wifi network
const char* ssid = "SSID";
const char* password = "PASSWORD";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;


// Auxiliar variables to store the current button state

String var1State = "Deactivated";  
String var2State = "Deactivated";  
String var3State = "Deactivated";
String var4State = "Deactivated";
String var5State = "Deactivated";
String var6State = "Deactivated";
String var7State = "Deactivated";




// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 

// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
 
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();


  
  //INITIALISATION of firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // sent the value of the header to serial monitor and to firebase
            if (header.indexOf("GET /P0507/on") >= 0) {
              Serial.println("PO507 on");
             var1State = "Activated";
             Firebase.setString("PO507", "Activated");
             
            } else if (header.indexOf("GET /P0507/off") >= 0) {
              Serial.println("P05076 off");
              var1State = "Deactivated";
              Firebase.setString("P0507", "Deactivated");

            } else if (header.indexOf("GET /P2067/on") >= 0) {
              Serial.println("P2067 on");
              var2State = "Activated";
              Firebase.setString("P2067", "Activated");
            } else if (header.indexOf("GET /P2067/off") >= 0) {
              Serial.println("P2067 off");
              var2State = "Deactivated";
              Firebase.setString("P2067", "Deactivated");
            
            } else if (header.indexOf("GET /P0100/on") >= 0) {
              Serial.println("P0100 on");
              var3State = "Activated";
              Firebase.setString("P0100", "Activated");
            } else if (header.indexOf("GET /P0100/off") >= 0) {
              Serial.println("P0100 off");
              var3State = "Desactivated";
              Firebase.setString("P0100", "Deactivated");
            

            } else if (header.indexOf("GET /P0515/on") >= 0) {
              Serial.println("P0515 on");
              var4State = "Activated";
              Firebase.setString("P0515", "Activated");
            } else if (header.indexOf("GET /P0515/off") >= 0) {
              Serial.println("P0515 off");
              var4State = "Deactivated";
              Firebase.setString("P0515", "Deactivated");
            

            } else if (header.indexOf("GET /P0802/on") >= 0) {
              Serial.println("P0802 on");
              var5State = "Activated";
              Firebase.setString("P0802", "Activated");
            } else if (header.indexOf("GET /P0802/off") >= 0) {
              Serial.println("P0802 off");
              var5State = "Deactivated";
              Firebase.setString("P0802", "Deactivated");
            

            } else if (header.indexOf("GET /P0218/on") >= 0) {
              Serial.println("P0218 on");
              var6State = "Activated";
              Firebase.setString("P0218", "Activated");
            } else if (header.indexOf("GET /P0218/off") >= 0) {
              Serial.println("P0218 off");
              var6State = "Deactivated";
              Firebase.setString("P0218", "Deactivated");
            

            } else if (header.indexOf("GET /P0217/on") >= 0) {
              Serial.println("P0217 on");
              var7State = "Activated";
              Firebase.setString("P0217", "Activated");
            } else if (header.indexOf("GET /P0217/off") >= 0) {
              Serial.println("P0217 off");
              var7State = "Deactivated";
              Firebase.setString("P0217", "Deactivated");
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // CSS to style the  buttons 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #555555; border: none; color: white; padding: 16px 100px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #ff8000;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>OBD-2 Emulator</h1>");
            
   
            client.println("<h2>OBD2 Trouble Codes </h2>");

            // Display current state, and change the state of buttons 
            //button P0507 
            client.println("<p>P0507 :High RPM - State " + var1State + "</p>");
                 
            if (var1State=="Deactivated") {
              client.println("<p><a href=\"/P0507/on\"><button class=\"button\">P0507 : Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/P0507/off\"><button class=\"button button2\">P0507 : Turn OFF</button></a></p>");
            } 
               
            //BUTTON P2067
            client.println("<p>P2067 FUEL level Low - State " + var2State + "</p>");
                   
            if (var2State=="Deactivated") {
              client.println("<p><a href=\"/P2067/on\"><button class=\"button\">P2067 : Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/P2067/off\"><button class=\"button button2\">P2067 : Turn OFF</button></a></p>");
            }
          
           // BUTTON P0100 
            client.println("<p>P0100 : Sonde de temperature batterie- panne du circuit - State  " + var4State + "</p>");
                  
            if (var4State=="Deactivated") {
              client.println("<p><a href=\"/P0100/on\"><button class=\"button\">P0100 : Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/P0100/off\"><button class=\"button button2\">P0100 : Turn OFF</button></a></p>");
            }

            // BUTTON P0515  
            client.println("<p>P0515 : Sonde de temperature batterie- panne du circuit - State  " + var4State + "</p>");
            \     
            if (var4State=="Deactivated") {
              client.println("<p><a href=\"/P0515/on\"><button class=\"button\">P0515 : Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/P0515/off\"><button class=\"button button2\">P0515 : Turn OFF</button></a></p>");
            }
            
            // BUTTON P0802 
            client.println("<p>P0802 Commande de transmission- Circuit Ouvert - State   " + var5State + "</p>");
                  
            if (var5State=="Deactivated") {
              client.println("<p><a href=\"/P0802/on\"><button class=\"button\">P0802 : Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/P0802/off\"><button class=\"button button2\">P0802 : Turn OFF</button></a></p>");
            }

            // BUTTON P0218
            client.println("<p>P0218 Surchauffe de la transmission - State " + var6State + "</p>");
            \      
            if (var6State=="Deactivated") {
              client.println("<p><a href=\"/P0218/on\"><button class=\"button\">P0218 : Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/P0218/off\"><button class=\"button button2\">P0218 : Turn OFF</button></a></p>");
            }

            // BUTTON P0217  
            client.println("<p>P0217 Surchauffe du moteur - State " + var7State + "</p>");
                
            if (var7State=="Deactivated") {
              client.println("<p><a href=\"/P0217/on\"><button class=\"button\">P0217 : Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/P0217/off\"><button class=\"button button2\">P0217 : Turn OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            
            client.println();
            // Break out of the while loop
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
