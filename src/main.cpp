/********** TEST ZONE *************/
#include "test/frameProtocol/uartFrame/uartFrameTest.hpp"
#include "test/asconCryptography/Ascon128aTest.hpp"
/********** TEST ZONE *************/

#include <Arduino.h>
#include <esp32-hal-cpu.h>
#include "setupConfiguration/utils.hpp"
#include "setupConfiguration/SetupNumberHelper.hpp"
#include "communication/Wifi.hpp"
#include "setupConfiguration/utils.hpp"
#include "transmission/Transmissions.hpp"

auto wifi = Wifi::create(WifiHelper::SSID, WifiHelper::PASSWORD);
auto ascon128a = Cryptography::Ascon128a::create();
auto controller = Transmissions::create();

int packetSuccess = 0;
int packetLoss = 0;

void setup() {
    setCpuFrequencyMhz(240);
    Serial.begin(Serial::BAUD_RATE);
    wifi->connect();
}

void loop() {
    static double totalTime = 0;
    static int timeCount = 0;

    controller->loopMqtt();
    auto startTime = std::chrono::high_resolution_clock::now();
    controller->startTransmissionProcess();
    auto endTime = std::chrono::high_resolution_clock::now();
    if(controller->m_transmissionNextState == TransmissionState::TRANSMISSION_ERROR) 
    {
        packetLoss++;
        PLAT_LOG_D("Success: %d - Loss: %d", packetSuccess, packetLoss);
    }
        
    else if(controller->m_transmissionNextState == TransmissionState::TRANSMISSION_COMPLETE) {
        packetSuccess++;
        PLAT_LOG_D("Success: %d - Loss: %d", packetSuccess, packetLoss);
    }
    double elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
    totalTime += elapsedTime;
    timeCount++;
    PLAT_LOG_D("Average Time: %.2f ms", totalTime / timeCount);
    __AIOT_FOR_MEDTECH_DESLAB__;
}

// Test::UartFrameTest::frameParserTest(); // Frame test passed
// Test::Ascon128aTest::RunAscon128aTest(); // Ascon test passed