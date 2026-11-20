#include "StorageEngine.hpp"
#include <stdexcept>

bool StorageEngine::evictIfExpired(const std::string &key) const
{
  if (key.empty())
    throw std::invalid_argument("Invalid key.");

  auto it = store.find(key);

  if (it == store.end())
    return false;

  if (Clock::now() >= it->second.expiresAt)
  {
    store.erase(key);
    ++expiredPurgedCount;
    return true;
  }
  return false;
}

bool StorageEngine::isExpired(const std::string &key) const
{
  if (key.empty())
    throw std::invalid_argument("Invalid key.");

  auto it = store.find(key);

  if (it == store.end())
    return false;

  if (Clock::now() >= it->second.expiresAt)
    return true;

  return false;
}

void StorageEngine::set(const std::string &key, const std::string &value)
{
  if (key.empty())
    throw std::invalid_argument("Invalid key.");

  auto expiry = Clock::now() + std::chrono::hours(1);

  store.insert_or_assign(key, Entry{value, expiry});
}

bool StorageEngine::exists(const std::string &key) const
{

  StorageEngine::evictIfExpired(key);

  return store.find(key) != store.end();
}
