#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

bool startListening = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin("Stadium Village", "");  //Connect to the WiFi network

  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection

    delay(500);
    Serial.println("Waiting to connect…");

  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());                         //Print the local IP of the webserver

  server.on("/heartbeat", handleHeartbeat);            //Associate the handler function to the path
  server.on("/numberRequest", handleNumberRequest);            //Associate the handler function to the path

  server.begin();                                                   //Start the server
  Serial.println("Server listening");
  randomSeed(analogRead(0));
}

void loop() {
  server.handleClient(); //Handling of incoming requests
}

void handleHeartbeat() { //Handler for the path
  //NEED TO HANDLE CORS REQUESTS - STEAL CODE FROM POSTMAN?
  server.send(200, "text/plain", "thump_thump\n");
  blinkLED();
}

void handleNumberRequest() { //Handler for the path
  //NEED TO HANDLE CORS REQUESTS - STEAL CODE FROM POSTMAN?
  server.send(200, "text/plain", String(random(1, 5)));
  blinkLED();
}

void blinkLED() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
}
