#pragma once

#include <chrono>
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <cstddef>

class StorageEngine
{
public:
  using Clock = std::chrono::steady_clock;
  using TimePoint = Clock::time_point;

  // For a single record
  struct Entry
  {
    std::string value;
    std::optional<TimePoint> expiresAt;
  };

private:
  // main storage for entries
  mutable std::unordered_map<std::string, Entry> store;

  // track how many entry has been deleted automatically on expiration
  mutable std::size_t expiredPurgedCount = 0;

  // check if entry has been expired.
  bool isExpired(const Entry &entry) const noexcept;

  // delete the expired entry
  void evictIfExpired(const std::string &key) const;

public:
  // insert a entry without expiration
  void set(const std::string &key, const std::string &value);

  // delete the expired entries and returns the active keys
  std::vector<std::string> keys() const;

  // returns the value if entry is not expired
  std::optional<std::string> get(const std::string &key) const;

  // Returns true if the key exists and has not expired
  bool exists(const std::string &key) const;

  // attach expiration time to existing entry
  bool expire(const std::string &key, const long long seconds) const;

  // return remaining ttl in seconds
  long long ttl(const std::string &key) const;

  // Returns total number of active keys
  std::size_t size() const;

  // Returns total number of purged keys since engine startup
  std::size_t purgedCount() const noexcept;

  // Exposes a read-only reference to the internal map for SnapshotManager binary serialization
  const std::unordered_map<std::string, Entry> &rawData() const noexcept;

  // Inserts a pre-built Entry directly into RAM during SnapshotManager binary recovery
  void loadRawEntry(const std::string &key, Entry entry);

  // Deletes a key from RAM
  bool del(const std::string &key);

  // Wipes all entries from memory
  void clear() noexcept;
};