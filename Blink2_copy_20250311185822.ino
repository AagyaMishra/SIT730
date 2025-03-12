#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define DHTPIN 2      // Pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11 or DHT22

// Wi-Fi and ThingSpeak settings
char ssid[] = "eduroam";       // Wi-Fi name
char pass[] = "aagya";   // Wi-Fi password
unsigned long myChannelNumber = 2872900; // ThingSpeak channel ID
const char * myWriteAPIKey = "FPA01IAVES252TCL"; // Write API key

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // If reading fails, retry
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Write data to ThingSpeak
  ThingSpeak.setField(1, t);   // Set field 1 to temperature
  ThingSpeak.setField(2, h);   // Set field 2 to humidity

  // Write data to the channel
  int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if (httpCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.println("Error sending data");
  }

  delay(60000);  // Wait 60 seconds before sending data again
}

