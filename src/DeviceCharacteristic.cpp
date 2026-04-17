#include "falcon-database/DeviceCharacteristic.hpp"
#include <iostream>

namespace falcon::database {

DeviceCharacteristicQuery::DeviceCharacteristicQuery() = default;

DeviceCharacteristicQuery::DeviceCharacteristicQuery(
    const DeviceCharacteristicQuery &) = default;

DeviceCharacteristicQuery::DeviceCharacteristicQuery(
    DeviceCharacteristicQuery &&) = default;

DeviceCharacteristicQuery &DeviceCharacteristicQuery::operator=(
    const DeviceCharacteristicQuery &) = default;

DeviceCharacteristicQuery &
DeviceCharacteristicQuery::operator=(DeviceCharacteristicQuery &&) = default;

DeviceCharacteristicQuery::~DeviceCharacteristicQuery() = default;

DeviceCharacteristicQuery::DeviceCharacteristicQuery(
    std::optional<std::string> scope, std::optional<std::string> name,
    std::optional<std::string> barrier_gate,
    std::optional<std::string> plunger_gate,
    std::optional<std::string> reservoir_gate,
    std::optional<std::string> screening_gate, std::optional<std::string> extra,
    std::optional<double> uncertainty, std::optional<std::string> hash,
    std::optional<int64_t> time, std::optional<std::string> state,
    std::optional<std::string> unit_name)
    : scope(std::move(scope)), name(std::move(name)),
      barrier_gate(std::move(barrier_gate)),
      plunger_gate(std::move(plunger_gate)),
      reservoir_gate(std::move(reservoir_gate)),
      screening_gate(std::move(screening_gate)), extra(std::move(extra)),
      uncertainty(uncertainty), hash(std::move(hash)), time(time),
      state(std::move(state)), unit_name(std::move(unit_name)) {}

bool DeviceCharacteristicQuery::operator==(
    const DeviceCharacteristicQuery &other) const {
  return scope == other.scope && name == other.name &&
         barrier_gate == other.barrier_gate &&
         plunger_gate == other.plunger_gate &&
         reservoir_gate == other.reservoir_gate &&
         screening_gate == other.screening_gate && extra == other.extra &&
         uncertainty == other.uncertainty && hash == other.hash &&
         time == other.time && state == other.state &&
         unit_name == other.unit_name;
}

bool DeviceCharacteristicQuery::operator!=(
    const DeviceCharacteristicQuery &other) const {
  return !(*this == other);
}

DeviceCharacteristic::DeviceCharacteristic() = default;

DeviceCharacteristic::DeviceCharacteristic(
    const std::string &scope, const std::string &name,
    const json &characteristic, std::optional<std::string> barrier_gate,
    std::optional<std::string> plunger_gate,
    std::optional<std::string> reservoir_gate,
    std::optional<std::string> screening_gate, std::optional<std::string> extra,
    std::optional<double> uncertainty, std::optional<std::string> hash,
    std::optional<int64_t> time, std::optional<std::string> state,
    std::optional<std::string> unit_name)
    : scope(scope), name(name), barrier_gate(std::move(barrier_gate)),
      plunger_gate(std::move(plunger_gate)),
      reservoir_gate(std::move(reservoir_gate)),
      screening_gate(std::move(screening_gate)), extra(std::move(extra)),
      uncertainty(uncertainty), hash(std::move(hash)), time(time),
      state(std::move(state)), unit_name(std::move(unit_name)),
      characteristic(characteristic) {}

json DeviceCharacteristic::to_json() const {
  json obj;
  obj["scope"] = scope;
  obj["name"] = name;

  auto put_opt = [&](const char *key, const auto &opt) {
    if (opt) {
      obj[key] = *opt;
    }
  };

  put_opt("barrier_gate", barrier_gate);
  put_opt("plunger_gate", plunger_gate);
  put_opt("reservoir_gate", reservoir_gate);
  put_opt("screening_gate", screening_gate);
  put_opt("extra", extra);
  put_opt("uncertainty", uncertainty);
  put_opt("hash", hash);
  put_opt("recordtime", time);
  put_opt("device_state", state);
  put_opt("unit_name", unit_name);
  obj["characteristic"] = characteristic;
  return obj;
}

DeviceCharacteristic DeviceCharacteristic::from_json(const json &j) {
  DeviceCharacteristic dchar;
  dchar.scope = j.value("scope", "");
  dchar.name = j.value("name", "");

  auto get_opt_str = [&](const char *key) -> std::optional<std::string> {
    return (j.contains(key) && !j[key].is_null())
               ? std::make_optional(j[key].get<std::string>())
               : std::nullopt;
  };
  auto get_opt_double = [&](const char *key) -> std::optional<double> {
    return (j.contains(key) && !j[key].is_null())
               ? std::make_optional(j[key].get<double>())
               : std::nullopt;
  };
  auto get_opt_int64 = [&](const char *key) -> std::optional<int64_t> {
    return (j.contains(key) && !j[key].is_null())
               ? std::make_optional(j[key].get<int64_t>())
               : std::nullopt;
  };

  dchar.barrier_gate = get_opt_str("barrier_gate");
  dchar.plunger_gate = get_opt_str("plunger_gate");
  dchar.reservoir_gate = get_opt_str("reservoir_gate");
  dchar.screening_gate = get_opt_str("screening_gate");
  dchar.extra = get_opt_str("extra");
  dchar.uncertainty = get_opt_double("uncertainty");
  dchar.hash = get_opt_str("hash");
  dchar.time = get_opt_int64("recordtime");
  dchar.state = get_opt_str("device_state");
  dchar.unit_name = get_opt_str("unit_name");

  dchar.characteristic = j["characteristic"];
  return dchar;
}

bool DeviceCharacteristic::operator==(const DeviceCharacteristic &other) const {
  return scope == other.scope && name == other.name &&
         barrier_gate == other.barrier_gate &&
         plunger_gate == other.plunger_gate &&
         reservoir_gate == other.reservoir_gate &&
         screening_gate == other.screening_gate && extra == other.extra &&
         uncertainty == other.uncertainty && hash == other.hash &&
         time == other.time && state == other.state &&
         unit_name == other.unit_name && characteristic == other.characteristic;
}

bool DeviceCharacteristic::operator!=(const DeviceCharacteristic &other) const {
  return !(*this == other);
}

DeviceCharacteristic::DeviceCharacteristic(const DeviceCharacteristic &) =
    default;

DeviceCharacteristic::DeviceCharacteristic(DeviceCharacteristic &&) = default;

DeviceCharacteristic &
DeviceCharacteristic::operator=(const DeviceCharacteristic &) = default;

DeviceCharacteristic &
DeviceCharacteristic::operator=(DeviceCharacteristic &&) = default;

DeviceCharacteristic::~DeviceCharacteristic() = default;

} // namespace falcon::database
