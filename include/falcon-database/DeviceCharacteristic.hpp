#pragma once

#include "falcon-database/export.h"
#include <cstdint>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace falcon::database {

using json = nlohmann::json;

/**
 * @brief Represents a possible query for a device characteristic which is
 * stored in the globals database
 */
struct FALCON_DATABASE_API DeviceCharacteristicQuery {
  std::optional<std::string> scope;
  std::optional<std::string> name;
  std::optional<std::string> barrier_gate;
  std::optional<std::string> plunger_gate;
  std::optional<std::string> reservoir_gate;
  std::optional<std::string> screening_gate;
  std::optional<std::string> extra;
  std::optional<double> uncertainty;
  std::optional<std::string> hash;
  std::optional<int64_t> time;
  std::optional<std::string> state;
  std::optional<std::string> unit_name;
  DeviceCharacteristicQuery();
  DeviceCharacteristicQuery(
      std::optional<std::string> scope, std::optional<std::string> name,
      std::optional<std::string> barrier_gate = std::nullopt,
      std::optional<std::string> plunger_gate = std::nullopt,
      std::optional<std::string> reservoir_gate = std::nullopt,
      std::optional<std::string> screening_gate = std::nullopt,
      std::optional<std::string> extra = std::nullopt,
      std::optional<double> uncertainty = std::nullopt,
      std::optional<std::string> hash = std::nullopt,
      std::optional<int64_t> time = std::nullopt,
      std::optional<std::string> state = std::nullopt,
      std::optional<std::string> unit_name = std::nullopt);
  bool operator==(const DeviceCharacteristicQuery &other) const;
  bool operator!=(const DeviceCharacteristicQuery &other) const;
  DeviceCharacteristicQuery(const DeviceCharacteristicQuery &);
  DeviceCharacteristicQuery(DeviceCharacteristicQuery &&);
  DeviceCharacteristicQuery &operator=(const DeviceCharacteristicQuery &);
  DeviceCharacteristicQuery &operator=(DeviceCharacteristicQuery &&);
  ~DeviceCharacteristicQuery();
};

/**
 * @brief Represents a device characteristic which is stored in the globals
 * database
 */
struct FALCON_DATABASE_API DeviceCharacteristic {
  std::string scope;
  std::string name;
  std::optional<std::string> barrier_gate;
  std::optional<std::string> plunger_gate;
  std::optional<std::string> reservoir_gate;
  std::optional<std::string> screening_gate;
  std::optional<std::string> extra;
  std::optional<double> uncertainty;
  std::optional<std::string> hash;
  std::optional<int64_t> time;
  std::optional<std::string> state;
  std::optional<std::string> unit_name;
  json characteristic;

  [[nodiscard]] json to_json() const;
  DeviceCharacteristic();
  DeviceCharacteristic(const std::string &scope, const std::string &name,
                       const nlohmann::json &characteristic,
                       std::optional<std::string> barrier_gate = std::nullopt,
                       std::optional<std::string> plunger_gate = std::nullopt,
                       std::optional<std::string> reservoir_gate = std::nullopt,
                       std::optional<std::string> screening_gate = std::nullopt,
                       std::optional<std::string> extra = std::nullopt,
                       std::optional<double> uncertainty = std::nullopt,
                       std::optional<std::string> hash = std::nullopt,
                       std::optional<int64_t> time = std::nullopt,
                       std::optional<std::string> state = std::nullopt,
                       std::optional<std::string> unit_name = std::nullopt);
  static DeviceCharacteristic from_json(const json &json);
  bool operator==(const DeviceCharacteristic &other) const;
  bool operator!=(const DeviceCharacteristic &other) const;
  DeviceCharacteristic(const DeviceCharacteristic &);
  DeviceCharacteristic(DeviceCharacteristic &&);
  DeviceCharacteristic &operator=(const DeviceCharacteristic &);
  DeviceCharacteristic &operator=(DeviceCharacteristic &&);
  ~DeviceCharacteristic();
};

} // namespace falcon::database
