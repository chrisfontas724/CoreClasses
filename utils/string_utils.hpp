// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <string> 

namespace cxl {
namespace utils {

inline uint64_t simpleHash(const std::string& str) {
    // fnv-1a
    uint64_t hash = 2166136261UL;
    if (str.c_str()){
        const char* c = str.c_str();
        while(*c != '\0') {
            hash = (hash ^ (*c++)) * 16777619;
        }
    }
    return hash;
}
        
inline uint64_t hash(const std::string& str) {
    return simpleHash(str);
}
 
inline std::string substringLastOccurence(const std::string& s, const char c) {
    std::string result = s;
    auto pos = result.rfind(c);
    if (pos != std::string::npos) {
        result.erase(0,pos+1);
    }
    return result;
}
        
inline bool containsSubstring(const std::string& s1, const std::string& s2) {
    return s1.find(s2) != std::string::npos;
}
        
inline std::string stringBetweenDeliminators(const std::string& string, 
                                             const std::string& first,
                                             const std::string& last) {
    uint64_t first_lim = string.find(first);
    uint64_t last_lim =  string.rfind(last);
    if (first_lim != std::string::npos && last_lim != std::string::npos) {
        std::string str_new = string.substr(first_lim, last_lim - first_lim);     
        str_new = str_new.substr(first.size());       
        return str_new;
    }
    return "";
}
        
inline bool replace(std::string& str, const std::string& from, const std::string& to) {
    uint64_t start_pos = str.find(from);
    if (start_pos == std::string::npos) {
        return false;
    }
    str.replace(start_pos, from.length(), to);
    return true;
}
        
inline bool replaceAll(std::string& str, const std::string& from, const std::string& to) {
    const std::string s = "*A";
    const std::string t = "*A\n";
    std::string::size_type n = 0;
    while ( ( n = str.find( from, n ) ) != std::string::npos ) {
        str.replace(n, from.size(), to);
        n += to.size();
    }
    return true;
}

} // utils
} // cxl

#endif // STRING_UTILS_HPP_
