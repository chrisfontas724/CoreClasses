// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef CORE_UTILS_HASHER_HPP_
#define CORE_UTILS_HASHER_HPP_

#include <string>

namespace cxl {
class Hasher {
   public:
    Hasher(uint32_t seed) : hash_(seed) {}

    void hashString(const std::string& str);

    void hashArray(uint32_t* arr, uint32_t num);

    template <typename T>
    void hash(T item) {
        hash_ = crc32(reinterpret_cast<const uint8_t*>(&item), sizeof(T), hash_);
    }

    uint32_t get_hash() const { return hash_; }

    static uint32_t simpleHash(const std::string& str);

   private:
    uint32_t crc32(const uint8_t* data, uint32_t size, uint32_t crc = 0);

private:

    uint32_t hash_ = 0;
};
}  // namespace cxl

#endif  // CORE_UTILS_HASHER_HPP_