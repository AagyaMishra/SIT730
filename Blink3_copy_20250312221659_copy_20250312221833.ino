#define LED_PIN 5  // LED connected to pin D5

void setup() {
    pinMode(LED_PIN, OUTPUT);  // Set LED as output
}

void loop() {
    float temperature = dht.readTemperature();

    if (!isnan(temperature)) {
        Serial.print("Temperature: "); Serial.println(temperature);

        if (temperature > 30.0) {
            digitalWrite(LED_PIN, HIGH); // Turn LED ON
            Serial.println("ALERT: High Temperature!");
        } else {
            digitalWrite(LED_PIN, LOW);  // Turn LED OFF
        }
    }

    delay(60000);
}
