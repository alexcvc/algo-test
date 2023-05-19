#include <fmt/format.h>
#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct TPhDeviceConfig {
  using TLDeviceNumbName = std::pair<uint8_t, std::string>;   ///< LDevice "relocation in ICD with domain name"
  std::vector<TLDeviceNumbName> bindedlDevices;               ///< LDevices binded with PhDevice
  std::string id;
};

void FillVectorDevices(std::vector<TPhDeviceConfig>& phDevices) {
  TPhDeviceConfig config;
  // first
  config.id = "A1";
  config.bindedlDevices.push_back(std::make_pair(0, "REGA"));
  config.bindedlDevices.push_back(std::make_pair(1, "REGB"));
  config.bindedlDevices.push_back(std::make_pair(2, "REGC"));
  config.bindedlDevices.push_back(std::make_pair(3, "REGD"));
  phDevices.push_back(config);

  // next
  config.bindedlDevices.clear();
  config.id = "E1";
  config.bindedlDevices.push_back(std::make_pair(4, "EORA"));
  config.bindedlDevices.push_back(std::make_pair(5, "EORB"));
  config.bindedlDevices.push_back(std::make_pair(6, "EORC"));
  config.bindedlDevices.push_back(std::make_pair(7, "EORD"));
  phDevices.push_back(config);

  // next
  config.bindedlDevices.clear();
  config.id = "D1";
  config.bindedlDevices.push_back(std::make_pair(8, "DPA"));
  config.bindedlDevices.push_back(std::make_pair(9, "DPB"));
  config.bindedlDevices.push_back(std::make_pair(10, "DPC"));
  config.bindedlDevices.push_back(std::make_pair(11, "DPD"));
  phDevices.push_back(config);
}

[[nodiscard]] std::optional<uint8_t> GetPhDeviceByLDeviceReloc(const std::vector<TPhDeviceConfig>& devices,
                                                               uint8_t reloc) {
  auto func = [&](const std::pair<uint8_t, std::string>& item) {
    return item.first == reloc;
  };
  for (uint8_t i = 0; i < devices.size(); ++i) {
    auto result = std::find_if(devices[i].bindedlDevices.begin(), devices[i].bindedlDevices.end(), func);
    if (result != devices[i].bindedlDevices.end()) {
      return i;
    }
  }
  return std::nullopt;
}

[[nodiscard]] std::optional<std::uint8_t> GetPhDeviceNumberByAEDeviceId(const std::vector<TPhDeviceConfig>& devices,
                                                                        std::string_view id) {
  auto result = std::find_if(devices.begin(),
                                                   devices.end(),
                                                   [&](const auto& val){ return val.id == id; } );
  if (result != devices.end()) {
    return std::distance(devices.begin(), result );
  }
  return std::nullopt;
}

int main() {
  std::vector<uint8_t> reloc{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 255};
  std::vector<std::string> idDevice{"A", "A1", "B", "B1", "C", "E", "E1", "D1", "D2"};
  std::vector<TPhDeviceConfig> phDevices;

  std::cout << "Test multi-relation" << std::endl;

  // add devices
  FillVectorDevices(phDevices);

  // find
  for (auto& it1 : reloc) {
    auto result = GetPhDeviceByLDeviceReloc(phDevices, it1);
    if (result.has_value()) {
      std::cout << fmt::format("PhDevice {} includes LDevices at relocation {}", result.value(), it1) << std::endl;
    } else {
      std::cout << fmt::format("Not fount PhDevice, that includes LDevices at relocation {}", it1) << std::endl;
    }
  }

  // find
  for (auto& it1 : idDevice) {
    auto result = GetPhDeviceNumberByAEDeviceId(phDevices, it1);
    if (result.has_value()) {
      std::cout << fmt::format("PhDevice={} has ID={}", result.value(), it1) << std::endl;
    } else {
      std::cout << fmt::format("Not fount PhDevice with ID={}", it1) << std::endl;
    }
  }
  return 0;
}
