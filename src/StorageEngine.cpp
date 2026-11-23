#include "StorageEngine.hpp"
#include <stdexcept>

const StorageEngine::Entry *StorageEngine::findValidEntry(const std::string &key) const
{
  if (key.empty())
    throw std::invalid_argument("Invalid key.");

  auto it = store.find(key);

  if (it == store.end())
    return nullptr;

  if (Clock::now() >= it->second.expiresAt)
  {
    store.erase(it);
    ++expiredPurgedCount;
    return nullptr;
  }

  return &(it->second);
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

  return findValidEntry(key) != nullptr;
}

std::optional<std::string> StorageEngine::get(const std::string &key) const

{
  const StorageEngine::Entry *entryPtr = findValidEntry(key);

  if (entryPtr == nullptr)
    return std::nullopt;

  return entryPtr->value;
}