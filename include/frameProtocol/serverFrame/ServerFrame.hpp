#include <stdint.h>
#include <memory>
#include <assert.h>
#include <vector>
#include "CRC16.hpp"
#include "FrameNumberHelper.hpp"
#include "setupConfiguration/utils.hpp"
#include "platform/platform.hpp"
#include "ellipticCurve/ecdh.hpp"
#include "communication/MQTT.hpp"

#define UART_FRAME_MAX_DATA_SIZE 255

/**
 * @brief The data will be construct following this frame before sending to device or receive from device.
 */
namespace Transmission
{
namespace ServerFrame
{
namespace Handshake
{
typedef struct __attribute__((packed))
{
    uint16_t s_preamble; // Sync bytes (e.g., 0xAA55)
    uint32_t s_identifierId; // Unique device/sensor ID
    uint8_t s_packetType; // 0x02 (Handshake)
    uint16_t s_sequenceNumber; // Monotonic counter for deduplication
    uint8_t s_publicKey[ECC_PUB_KEY_SIZE]; //Public key for encryption (32 bytes)
    uint8_t s_authTag[AUTH_TAG_SIZE]; // Integrity/authentication tag
} HandshakeFrameData;
}

namespace DataFrame
{
typedef struct __attribute__((packed))
{
    uint16_t s_preamble;           // Sync bytes (e.g., 0xAA55)
    uint32_t s_identifierId;       // Unique device/sensor ID
    uint8_t s_packetType;          // 0x01 (DATA)
    uint16_t s_sequenceNumber;     // Monotonic counter for deduplication
    uint64_t s_timestamp;          // Timestamp (Unix epoch or device time)
    uint8_t s_nonce[NONCE_SIZE];           // Unique 128-bit nonce for encryption
    uint16_t s_payloadLength;      // Length of encrypted payload (0-1024 bytes)
    uint8_t s_encryptedPayload[ENCRYPTED_PAYLOAD_SIZE]; // Encrypted data (Ascon-128)
    uint8_t s_authTag[AUTH_TAG_SIZE];         // Integrity/authentication tag
} ServerFrameData;
}

class ServerFrame
{
private:
    std::shared_ptr<Handshake::HandshakeFrameData> m_handshakeFrame;
    std::shared_ptr<DataFrame::ServerFrameData> m_serverFrame;
    uint16_t m_dataLength;
    uint16_t m_crcReceive;
    std::vector<uint8_t> m_frameBuffer;
    HandshakeState m_handshakeNextState;
    uint32_t m_lastByteTimestamp;
    bool m_isParsingActive = false;
public:
    /**
     * @brief Constructor of UartFrame
     */
    ServerFrame();

    /**
     * @brief Destructor of UartFrame
     */
    ~ServerFrame();

    /**
     * @brief Smart pointer to create ServerFrameData object
     * @return A shared pointer to a new ServerFrameData object
     */
    static std::shared_ptr<ServerFrame> create();

    /**
     * @brief Perform handshake with server to acquire encryption key
     */
    void performHandshake(std::shared_ptr<MQTT> mqtt);

    /**
     * @brief Reset handshake state machine
     */
    void resetHandshakeState();

    /**
     * @brief Get the current handshake state
     * @return The current handshake state
     */
    HandshakeState getHandshakeState();
};
}
} // namespace Communication::UartFrame
