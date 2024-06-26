#pragma once

#include "Common.h"
#include "Protocol.h"

namespace EspNowRcLink {

class Receiver {
public:
  enum State {
    BEACON,
    PAIR,
    RECEIVING,
  };

  Receiver();
  int begin(bool enSoftAp = false);
  int update();
  int available();
  int16_t getChannel(int c) const;
  int setSensor(int sensorId, int sensorValue);

private:
  void _handleBeacon();
  void _handlePair();
  void _handleAlive();

  bool _allowed(const uint8_t *mac) const;
  static void _handleRx(const uint8_t *mac, const uint8_t *buf, size_t count, void *arg) IRAM_ATTR;
  static const uint8_t BCAST_PEER[WIFIESPNOW_ALEN];

  volatile MessageRc _channels;
  MessageFc _sensors;
  uint8_t _peer[WIFIESPNOW_ALEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint32_t _next_beacon = 0;
  uint32_t _next_alive = 0;
  State _state = RECEIVING; //No pair
  volatile bool _new_data = false;
};

}
