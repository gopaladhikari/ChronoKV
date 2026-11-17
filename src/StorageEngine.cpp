
#include <iostream>
#include "StorageEngine.hpp"
#include <chrono>
#include <string>
#include <optional>
#include <unordered_map>

using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;

struct Entry
{
  std::string value;
  std::optional<TimePoint> expiresAt;
};

class StorageEngine
{
private:
  mutable std::unordered_map<std::string, Entry> store;
  mutable std::size_t expiredPurgedCount_ = 0;
};