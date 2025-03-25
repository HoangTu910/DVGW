#ifndef MQTT_HPP
#define MQTT_HPP

#include <PubSubClient.h>
#include <WiFi.h>
#include <memory>
#include "setupConfiguration/utils.hpp"
#include "communication/CommunicationNumberHelper.hpp"
#include "ellipticCurve/ecdh.hpp"
#include "frameProtocol/FrameNumberHelper.hpp"

class MQTT
{
private:
    char *m_mqttUser;
    char *m_mqttPassword;
    char *m_mqttServer;
    int m_mqttPort;
    char *m_mqttDeviceID;
    char *m_mqttDataTopic;
    char *m_mqttPublicKeyTopic;
    char *m_mqttPublicKeyReceiveTopic;
    WiFiClient m_espClient;
    PubSubClient m_client;
public:
    //constructor
    uint8_t m_mqttCallBackDataReceive[ECC_PUB_KEY_SIZE];
    bool m_mqttIsMessageArrived = false;
    bool m_mqttIsAckPackageArrived = false;
    bool m_mqttIsSequenceNumberNeededUpdate = false;
    bool m_mqttIsTimeout = false;
    MQTT(char *mqttServer, int mqttPort, char *mqttDeviceID, char *mqttDataTopic, char *mqttPublicKeyTopic, char *mqttUser, char *mqttPassword, char *mqttPublicKeyReceiveTopic);
    ~MQTT();

    //setter
    void setMqttServer(char *mqttServer);
    void setMqttPort(int mqttPort);
    void setMqttDeviceID(char *mqttDeviceID);
    void setMqttDataTopic(char *mqttDataTopic);
    void setMqttPublicKeyTopic(char *mqttPublicKeyTopic);
    void setMqttClient();

    //getter
    char *getMqttServer();
    int getMqttPort();
    char *getMqttDeviceID();
    char *getMqttDataTopic();
    char *getMqttPublicKeyTopic();

    //configuration
    void callBack(char *topic, byte *payload, unsigned int length);
    void connect();
    void reconnect();
    void setupServer();

    bool publishData(const void *data, size_t dataLength);

    static std::shared_ptr<MQTT> create(
        char *mqttServer, 
        int mqttPort, 
        char *mqttDeviceID, 
        char *mqttDataTopic,
        char *mqttPublicKeyTopic, 
        char *mqttUser, 
        char *mqttPassword,
        char *mqttPublicKeyReceiveTopic);
};

#endif // MQTT_HPP