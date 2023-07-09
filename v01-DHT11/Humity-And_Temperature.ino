#include <DHT.h>
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(000,000,000,00);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "password";        // MySQL user login password

#define DHTPIN D2 // The DHT11 sensor was connected to pin D2
#define DHTTYPE DHT11

// WiFi card example
char ssid[] = "your-ssid";         // your SSID - wifi network name
char pass[] = "your-password";     // your SSID Password

// Simple query, but change as per your need
char INSERT_DATA[] = "INSERT INTO database_name.table_name (id_sensor, avatar, measurement_type, sensor_value, unit) VALUES (%d,'%s',%d,'%s',%d)";

WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();    // Inicialize DHT sensor
  CheckWiFi();    // Function to starting and verify WiFi Connection
}

void loop() {
  SendData(0);    // Function to send and insert temperature value  
  delay(5000);
  
  SendData(1);    // Function to send and insert humidity value
  delay(3600000);
}

void CheckWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.printf("\nNo connection... connecting to WiFi network %s", ssid);
    WiFi.disconnect();
    delay(1000);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.printf("\nStarting WiFi network connection %s. >> ", ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

  } else {
    Serial.printf("\n*connected to WiFi network %s. >> ", ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  delay(1000);
}

void SendData(int type){

  float sensor_value;
  char query[150];
  char sensor_new[10];
  
  if(type == 0){
    sensor_value = dht.readTemperature();
  } else {
    sensor_value = dht.readHumidity();
  }
  
  CheckWiFi();
  if (conn.connect(server_addr, 3306, user, password)){
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    dtostrf(sensor_value, 5, 2, sensor_new);
    Serial.println(sensor_new);
    sprintf(query, INSERT_DATA, 1, "Sensor_Name", type, sensor_new, type);
    Serial.println(query);
    cur_mem->execute(query);
    delete cur_mem;
    Serial.println("Success!");
  } else {
    Serial.println("Failed to insert data!");
  }
  conn.close();
}
