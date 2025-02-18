#pragma once

#define BYTE_MAX 255
#define KILO_BYTE_MAX 1024
#define AUTH_TAG_SIZE 16
#define PUBLIC_KEY_SIZE 32
#define ENCRYPTED_PAYLOAD_SIZE 256
#define NONCE_SIZE 16

#define IGNORE_PADDING __attribute__((packed))

enum UartFrameConstants
{
    UART_FRAME_HEADER_1 = 0xAB,
    UART_FRAME_HEADER_2 = 0xCD,
    UART_FRAME_TRAILER_1 = 0xE1,
    UART_FRAME_TRAILER_2 = 0xE2
};

enum Dummy
{
    DUMMY = 0x00
};

enum UartTimer
{
    UART_FRAME_TIMEOUT_MS = 100
};

enum UartParserState
{
    VERIFY_HEADER_1_BYTE,
    VERIFY_HEADER_2_BYTE,
    WAIT_FOR_DATA_LENGTH_1_BYTE,
    WAIT_FOR_DATA_LENGTH_2_BYTE,
    RECEIVE_DATA,
    VERIFY_TRAILER_1_BYTE,
    VERIFY_TRAILER_2_BYTE,
    WAIT_FOR_CRC_1_BYTE,
    WAIT_FOR_CRC_2_BYTE,
    VERIFY_CRC,
    FRAME_COMPLETE,
    FRAME_ERROR
};

enum ServerFrameConstants
{
    SERVER_FRAME_PREAMBLE = 0xAA55,
    SERVER_FRAME_IDENTIFIER_ID = 0x08110910,
    SERVER_FRAME_PACKET_HANDSHAKE_TYPE = 0x03,
    SERVER_FRAME_PACKET_DATA_TYPE = 0x01,
    SERVER_FRAME_PACKET_ACK_TYPE = 0x02,
    SERVER_FRAME_SEQUENCE_NUMBER = 9,
    SERVER_FRAME_END_MAKER = 0xAABB,
    RESET_SEQUENCE = 0
};

const uint8_t SERVER_FRAME_AUTH_TAG[AUTH_TAG_SIZE] = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18, 0x29, 0x3A, 0x4B, 0x5C, 0x6D, 0x7E, 0x8F, 0x90};

enum HandshakeState
{
    GENERATE_PUBLIC_KEY,
    CONSTRUCT_PUBLIC_KEY_FRAME,
    SEND_PUBLIC_KEY_FRAME,
    WAIT_FOR_PUBLIC_FROM_SERVER,
    COMPUTE_SHARED_SECRET,
    HANDSHAKE_COMPLETE
};