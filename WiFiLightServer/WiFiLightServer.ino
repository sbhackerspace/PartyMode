/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
#include "WifiNetworkData.h" //ssid name and wifi password

void printResponse(WiFiClient c, int value);

void printResponse(WiFiClient c, int value){
    // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/json\r\n\r\n{\"lights\":";
  s += (value)?"\"1":"\"0";
  s += "\"}";

  // Send the response to the client
  c.print(s);
  delay(1);
}


// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

int wifiDownCount = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  WiFi.mode(WIFI_STA);
  connectToWifiNetwork();
}

int val;

void loop() {
  if (WiFi.status() != WL_CONNECTED)
  {
    connectToWifiNetwork();
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  if (req.indexOf("/off") != -1){
    val = 0;
    printResponse(client, val);
    digitalWrite(2, val);
  }
  else if (req.indexOf("/on") != -1){
    val = 1;
    printResponse(client, val);
    digitalWrite(2, val);
  }
  else if (req.indexOf("/status") != -1){
    printResponse(client, val);
  }
  else if(req.indexOf("/help") != -1){
    client.print("Available commands:\r\non\r\noff\r\nstatus");
    delay(1);
  }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  client.flush();

  Serial.println("Client disonnected");
  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

void connectToWifiNetwork()
{
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}
