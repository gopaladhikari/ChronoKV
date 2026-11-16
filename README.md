# ChronoKV

**ChronoKV** is a lightweight, persistent, in-memory key-value storage engine written in **Modern C++ (C++20)**. Designed with clean object-oriented separation, deterministic memory management (RAII), and binary disk persistence, it provides $O(1)$ average-time lookups alongside automatic Time-To-Live (TTL) key expiration.

---

## Key Engineering Features

- **$O(1)$ In-Memory Hash Store:** Built on `std::unordered_map` for constant-time insertions, lookups, and deletions.
- **Deterministic TTL Expiration Engine:** Leverages `std::chrono::steady_clock` (monotonic clock) to prevent system-clock drift bugs when expiring keys via `EXPIRE` and `TTL`.
- **Zero-Overhead Binary Persistence:** Serializes memory state to disk using custom length-prefixed binary encoding (`std::ios::binary`), avoiding slow text parsing and delimiter collisions.
- **Resilient I/O & Error Handling:** Utilizes C++17 `<filesystem>` for safe path/directory management, strict stream state validation (`eof`, `fail`, `bad`), and a custom exception hierarchy inheriting from `std::runtime_error`.
- **Modern C++ Memory Safety:** Strictly adheres to RAII principles using `std::unique_ptr`, `std::optional`, `const`-correctness, and `noexcept` guarantees—eliminating raw `new`/`delete` memory hazards.

---

## System Architecture

```text
+-------------------------------------------------------------------+
|                         REPL Client (CLI)                         |
+---------------------------------+---------------------------------+
                                  | Raw Command String
                                  v
+-------------------------------------------------------------------+
|                     CommandRouter (.hpp/.cpp)                     |
|         Tokenizes input & validates syntax/arguments              |
+----------------+---------------------------------+----------------+
                 |                                 |
                 v                                 v
+---------------------------------+ +-------------------------------+
|    StorageEngine (.hpp/.cpp)    | |   SnapshotManager (.hpp/.cpp) |
| - std::unordered_map<K, Entry>  | | - Binary stream serialization |
| - Lazy TTL eviction checks      | | - std::filesystem management  |
| - Memory & hit/miss telemetry   | | - Stream state validation     |
+---------------------------------+ +-------------------------------+
```
