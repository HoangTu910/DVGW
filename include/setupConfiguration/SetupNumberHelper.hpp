#ifndef SETUP_NUMBER_HELPER_HPP
#define SETUP_NUMBER_HELPER_HPP

#define __AIOT_FOR_MEDTECH_DESLAB__ delay(500)

enum Serial
{
    BAUD_RATE = 115200,
    TX_PIN = 16,
    RX_PIN = 17,
};

enum TransmissionState
{
    TRANSMISSION_IDLE,
    PROCESS_FRAME_PARSING,
    HANDSHAKE_AND_KEY_EXCHANGE,
    PROCESS_ENCRYPTION,
    SEND_DATA_TO_SERVER,
    WAIT_FOR_ACK_PACKAGE,
    TRANSMISSION_COMPLETE,
    TRANSMISSION_ERROR
};

enum Device
{
    Identifier = 0x01,
    BYTE_LENGTH = 4
};

#endif // SETUP_NUMBER_HELPER_HPP
