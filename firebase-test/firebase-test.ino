#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#define FIREBASE_HOST "dummy-99011.firebaseio.com" // the project name address from firebase id
#define FIREBASE_AUTH "LrI5IPWjVYUyJj6KBlv7NPYrORTEcTpJjebp8a3l" // the secret key generated from firebase
#define WIFI_SSID "André Tryk" // input your home or public wifi name 
#define WIFI_PASSWORD "Test1234" //password of wifi ssid
#define DHTPIN D4 // what digital pin we're connected to
#define DHTTYPE DHT11 // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);                                                     

String fireStatus = ""; // led status received from firebase
int led = D3; // for external led

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);      
  pinMode(led, OUTPUT); 
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(); 
  Serial.print("Connected to "); //Writes the SSID on the connected wifi to the serial moniter
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP()); //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase
  dht.begin(); //Start reading dht sensor
  Firebase.setString("LED_STATUS", "OFF"); //Sets the led status to off
}

void loop() { 

  fireStatus = Firebase.getString("LED_STATUS"); // get led status input from firebase
  if (fireStatus == "ON") { // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW); // make bultin led ON
    digitalWrite(led, HIGH); // make external led ON
  } 
  else if (fireStatus == "OFF") { // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH); // make bultin led OFF
    digitalWrite(led, LOW); // make external led OFF
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
  
  float h = dht.readHumidity(); // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature(); // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) { // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!")); //write to the serial moniter if any readings of the sensor fails
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%"); //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("°C ");
  String fireTemp = String(t) + String("°C"); //convert integer temperature to string temperature
  delay(1000); // wait for a second before next reading
  
  Firebase.pushString("/DHT11/Humidity", fireHumid); //setup path and send readings
  Firebase.pushString("/DHT11/Temperature", fireTemp); //setup path and send readings
}
