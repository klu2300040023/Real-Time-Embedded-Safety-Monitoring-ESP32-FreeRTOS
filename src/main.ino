#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// ----------- PIN DEFINITIONS -----------
#define DHTPIN 4
#define DHTTYPE DHT11

#define MQ2_PIN 34
#define PIR_PIN 27
#define RELAY_PIN 26
#define BUZZER_PIN 25

// ----------- OBJECTS -----------
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ----------- WIFI & THINGSPEAK -----------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
String apiKey = "YOUR_THINGSPEAK_API_KEY";
const char* server = "http://api.thingspeak.com/update";

// ----------- GLOBAL VARIABLES -----------
float temperature = 0;
float humidity = 0;
int smokeValue = 0;
int pirValue = 0;
float hazardIndex = 0;

// ----------- SENSOR TASK -----------
void SensorTask(void *pvParameters) {
  while (1) {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    smokeValue = analogRead(MQ2_PIN);
    pirValue = digitalRead(PIR_PIN);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

// ----------- DECISION TASK -----------
void DecisionTask(void *pvParameters) {
  while (1) {
    hazardIndex = (smokeValue * 0.4) + (temperature * 3) + (pirValue * 50);

    if (hazardIndex > 300) {
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
    }

    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}

// ----------- DISPLAY TASK -----------
void DisplayTask(void *pvParameters) {
  while (1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Haz:");
    lcd.print(hazardIndex);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

// ----------- CLOUD TASK -----------
void CloudTask(void *pvParameters) {
  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(server) + "?api_key=" + apiKey +
                   "&field1=" + String(temperature) +
                   "&field2=" + String(humidity) +
                   "&field3=" + String(smokeValue) +
                   "&field4=" + String(hazardIndex);

      http.begin(url);
      http.GET();
      http.end();
    }
    vTaskDelay(15000 / portTICK_PERIOD_MS);
  }
}

// ----------- SETUP -----------
void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  xTaskCreate(SensorTask, "SensorTask", 4096, NULL, 1, NULL);
  xTaskCreate(DecisionTask, "DecisionTask", 4096, NULL, 2, NULL);
  xTaskCreate(DisplayTask, "DisplayTask", 4096, NULL, 1, NULL);
  xTaskCreate(CloudTask, "CloudTask", 4096, NULL, 1, NULL);
}

void loop() {
  // Empty loop (FreeRTOS handles everything)
}
