#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Konfigurasi sensor DHT11
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* myNim = "G.231.20.0136";

// Konfigurasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Konfigurasi WiFi dan MQTT Broker
const char* ssid = "Yans Rice Bowl";
const char* password = "sambelijo";
const char* mqtt_server = "usm.revolusi-it.com";
const char* user_mqtt = "usm";
const char* pass_mqtt = "usmjaya24";
const char* topik = "test/test";

WiFiClient espClient;
PubSubClient client(espClient);
String messages;

// Function callback ketika menerima pesan dari MQTT server
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Pesan dari MQTT [");
    Serial.print(topic);
    Serial.print("] ");

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, payload, length);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

    const char* nim = doc["nim"];
    const char* messages = doc["messages"];



    // unsigned long start = millis();
    if (String(nim) == myNim) {
        if (String(messages) == "D5=1") { digitalWrite(D5, HIGH); }
        if (String(messages) == "D6=1") { digitalWrite(D6, HIGH); }
        if (String(messages) == "D7=1") { digitalWrite(D7, HIGH); }
        if (String(messages) == "D8=1") { digitalWrite(D8, HIGH); }

        if (String(messages) == "D5=0") { digitalWrite(D5, LOW); }
        if (String(messages) == "D6=0") { digitalWrite(D6, LOW); }
        if (String(messages) == "D7=0") { digitalWrite(D7, LOW); }
        if (String(messages) == "D8=0") { digitalWrite(D8, LOW); }
    } else {
        Serial.println("LED tidak bisa dikontrol, NIM harus sesuai!");
    }

     Serial.println("");
     Serial.print("NIM: ");
     Serial.print(nim);
     Serial.print(" Messages: ");
     Serial.println(messages);
    // unsigned long end = millis();
    // Serial.print("Processing time: ");
    // Serial.print(end - start);
    // Serial.println(" ms");
}

void reconnect() {
    // Looping sampai terkoneksi ke MQTT server
    while (!client.connected()) {
        Serial.println("Menghubungkan ke MQTT Server...");

        // Mencoba menghubungkan ke MQTT server
        if (client.connect(myNim, user_mqtt, pass_mqtt)) {
            Serial.println("Terhubung ke MQTT server " + String(mqtt_server));
            // Berlangganan ke topik
            client.subscribe(topik);
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" coba lagi dalam 5 detik...");
            delay(5000);
        }
    }
}

void konek_wifi() {
    delay(10);
    Serial.println();

    WiFi.begin(ssid, password);

    Serial.print("Menyambungkan ke WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Berhasil terhubung ke WiFi ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

// Fungsi untuk mengirim data sensor ke MQTT server
void publishData(float temperature, float humidity) {
    StaticJsonDocument<256> doc;
    doc["nim"] = myNim;
    doc["suhu"] = temperature;
    doc["kelembaban"] = humidity;

    char buffer[256];
    size_t n = serializeJson(doc, buffer);

    Serial.print("Publishing data: ");
    Serial.println(buffer);

    client.publish(topik, buffer, n);
}

// Fungsi untuk inisialisasi pin
void initPins() {
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
}

void setup() {

    // Memulai komunikasi ke serial monitor
    Serial.begin(9600);
    Wire.begin(D1, D2); // Aktivasi D1 dan D2 sbg pin I2C
    lcd.begin(16, 2);
    lcd.backlight();

    // menjalankan sensor DHT11
    dht.begin();

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    // Inisialisasi pin
    initPins();

    // Menghubungkan ke WiFi
    konek_wifi();
}

void loop() {
    // Cek koneksi WiFi
    if (WiFi.status() != WL_CONNECTED) {
        konek_wifi();
    }

    // Cek koneksi ke MQTT server
    if (!client.connected()) {
        reconnect();
    }

    client.loop();

    static unsigned long lastPublishTime = 0;
    // cek data suhu dan kelembaban akan dipublish setiap 2 detik
    if (millis() - lastPublishTime >= 2000) {
        lastPublishTime = millis();
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        // Cek jika DHT 11 tidak mendeteksi suhu dan kelembaban
        if (isnan(t) || isnan(h)) {
            Serial.println("Gagal membaca suhu dan kelembaban dari sensor DHT!");
            return;
        }

        // Menampilkan suhu dan kelembaban di LCD display
        lcd.setCursor(0, 0);
        lcd.print("Suhu: " + String(t) + "C");
        lcd.setCursor(0, 1);
        lcd.print("Kelembaban: " + String(h) + "%");

        // Publish suhu dan kelembaban ke MQTT server
        publishData(t, h);
    }
}
