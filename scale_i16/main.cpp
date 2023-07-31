#include <fmt/format.h>
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>

std::array<uint8_t, 2> m_octets{0, 0};

void SetScaledValueI16(int sVal, uint8_t ucOffset) {
  m_octets[ucOffset + 2] &= ~0x01;

  if (sVal < -32768) {
    m_octets[ucOffset] = m_octets[ucOffset + 1] = 0xff;
    m_octets[ucOffset + 2] |= 0x01;
  } else if (sVal > 32767) {
    m_octets[ucOffset] = 0xff;
    m_octets[ucOffset + 1] = 0x7f;
    m_octets[ucOffset + 2] |= 0x01;
  } else {
    uint16_t usVal{static_cast<uint16_t>(sVal)};
    m_octets[ucOffset] = static_cast<uint8_t>((usVal & 0x00ff) & 0xff);
    m_octets[ucOffset + 1] = static_cast<uint8_t>(((usVal & 0xff00) >> 8) & 0xff);
  }
}

void printResult(int iecScaled, int& value, int& offset) {
  std::cout << fmt::format("value={:<8d} offset={:d} hex=[{:#04x}{:02x}] | bin=[{:08b} {:08b}] | {:d}", value, offset,
                           m_octets[1], m_octets[0], m_octets[1], m_octets[0], iecScaled)
            << std::endl;
}
int main() {

  int value;
  auto offset{0};
  auto maxVal{USHRT_MAX * 2};

  std::cout << "--- positive" << std::endl;

  for (value = 1; value < maxVal; value *= 2) {
    m_octets = {0, 0};
    SetScaledValueI16(value, offset);
    int iecScaled = (uint16_t)(m_octets[offset] | (m_octets[offset + 1] << 8));
    printResult(iecScaled, value, offset);
  }

  std::cout << "--- negative" << std::endl;

  for (value = -1; value > -maxVal; value *= 2) {
    m_octets = {0, 0};
    SetScaledValueI16(value, offset);
    int iecScaled = (uint16_t)(m_octets[offset] | (m_octets[offset + 1] << 8));
    printResult(iecScaled, value, offset);
  }

  std::cout << "--- near max negative" << std::endl;

  for (value = -32765; value > -32770; --value) {
    m_octets = {0, 0};
    SetScaledValueI16(value, offset);
    int iecScaled = (uint16_t)(m_octets[offset] | (m_octets[offset + 1] << 8));
    printResult(iecScaled, value, offset);
  }
  return 0;
}
