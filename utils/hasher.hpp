// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef CORE_UTILS_HASHER_HPP_
#define CORE_UTILS_HASHER_HPP_

#include <string>

namespace cxl {
class Hasher {
public:
        
        uint32_t hashString(const std::string& str);
        
        uint32_t hashArray(uint32_t* arr, uint32_t num);
        
        template<typename T>
        uint32_t hash(T item, uint32_t seed) {
            return crc32(static_cast<uint8_t*>(&item), sizeof(T), seed);
        }

    static uint32_t simpleHash(const std::string& str);
private:
        
    uint32_t crc32(const uint8_t* data, uint32_t size, uint32_t crc = 0);

};
} // cxl

#endif // CORE_UTILS_HASHER_HPP_