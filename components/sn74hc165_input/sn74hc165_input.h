#include "esphome.h"

class SN74HC165Input : public PollingComponent, public BinarySensor {
public:
  SN74HC165Input(uint8_t bit_number) : pinNum(bit_number) {}

  void setup() override {
    pinMode(loadPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, INPUT_PULLUP);
    digitalWrite(loadPin, HIGH);
  }

  void update() override {
    // Зчитування всіх 8 бітів, беремо тільки наш біт
    digitalWrite(loadPin, LOW);
    delayMicroseconds(5);
    digitalWrite(loadPin, HIGH);

    digitalWrite(clockPin, LOW);
    bool bit_state = digitalRead(dataPin);
    digitalWrite(clockPin, HIGH);

    publish_state(!bit_state); // кнопка замкнута на GND -> інверсія
  }

private:
  uint8_t pinNum;
  const uint8_t loadPin = 25;   // підключення LATCH
  const uint8_t clockPin = 26;  // підключення CLOCK
  const uint8_t dataPin = 27;   // підключення DATA
};
