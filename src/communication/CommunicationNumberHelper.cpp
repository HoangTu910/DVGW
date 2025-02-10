// communication_number_helper.cpp
#include "communication/CommunicationNumberHelper.hpp"

namespace WifiHelper
{
    // char *SSID = (char*)"The Jade Coffee and Tea";
    // char *PASSWORD = (char*)"caphengon";

    // char *SSID = (char*)"Dau Cafe Ngoai Troi";
    // char *PASSWORD = (char*)"Mocua24h";

    char *SSID = (char*)"Hoang Tuan";
    char *PASSWORD = (char*)"03081973";
}

namespace MQTTHelper
{   
    char* MQTT_SERVER = (char*)"113.161.225.11";
    int MQTT_PORT = 1885;
    char* MQTT_USER = (char*)"admin";
    char* MQTT_PASSWORD = (char*)"123";
    char* MQTT_DATA_TOPIC = (char*)"sensors/data";
    char* MQTT_PUBLIC_KEY_TOPIC = (char*)"handshake/ecdh";
    char* MQTT_DEVICE_ID = (char*)"newdevice123";
    char* MQTT_PUBLIC_KEY_RECEIVE_TOPIC = (char*)"handshake-send/ecdh";
    int MQTT_TIMEOUT = 5000;
}
