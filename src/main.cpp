/********** TEST ZONE *************/
#include "test/frameProtocol/uartFrame/uartFrameTest.hpp"
#include "test/asconCryptography/Ascon128aTest.hpp"
/********** TEST ZONE *************/

#include <Arduino.h>
#include "setupConfiguration/utils.hpp"
#include "setupConfiguration/SetupNumberHelper.hpp"
#include "communication/MQTT.hpp"
#include "communication/Wifi.hpp"
#include "setupConfiguration/utils.hpp"

auto mqtt = MQTT::create(
      MQTTHelper::MQTT_SERVER, 
      MQTTHelper::MQTT_PORT, 
      MQTTHelper::MQTT_DEVICE_ID, 
      MQTTHelper::MQTT_DATA_TOPIC, 
      MQTTHelper::MQTT_PUBLIC_KEY_TOPIC,
      MQTTHelper::MQTT_USER,
      MQTTHelper::MQTT_PASSWORD);
auto wifi = Wifi::create(WifiHelper::SSID, WifiHelper::PASSWORD);
auto ascon128a = Cryptography::Ascon128a::create();

void setup() {
    Serial.begin(Serial::BAUD_RATE);
    Serial1.begin(Serial::BAUD_RATE, SERIAL_8N1, Serial::RX_PIN, Serial::TX_PIN);
    wifi->connect();
    mqtt->setupServer();
}

void loop() {
    mqtt->connect();
    // Test::UartFrameTest::frameParserTest(); // Frame test passed
    Test::Ascon128aTest::RunAscon128aTest(); // Ascon test passed
    delay(5000);
}

