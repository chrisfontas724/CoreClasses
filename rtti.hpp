// Copyright 2019 Chris Fontas. All rights reserved.
// Use of this source code is governed by the license that can be
// found in the LICENSE file.

#ifndef RTTI_HPP_
#define RTTI_HPP_

#include <functional>
#include <map>
#include <string>

namespace cxl {

inline uint64_t simpleHash(const std::string& str);

class RTTI {
public:
        
    RTTI(std::string class_name, const RTTI* base_rtti)
        : class_name_(class_name)
        , class_id_(simpleHash(class_name))
        , base_rtti_(base_rtti) {
            auto& map = flags_map();
            index_ = map[base_rtti]++;
        }
        
    const RTTI* base_rtti()  const { return base_rtti_;  }
    std::string class_name() const { return class_name_; }
    uint32_t    class_id()   const { return class_id_;   }
    uint32_t    index()      const { return index_;      }
        
    inline bool isTypeOf(const RTTI* base) const {
        const RTTI* rtti = this;
        while(rtti) {
            if(rtti && base && rtti->class_id_ == base->class_id_) {
                return true;
            }
            rtti = rtti->base_rtti_;
        }
        return false;
    }
        
    inline bool isType(const RTTI* type) const {
            return (this == type);
    }
        
protected:
    const RTTI* base_rtti_;
    std::string class_name_;
    uint32_t class_id_;
    uint32_t index_;
    
    static std::map<const RTTI*, uint32_t>& flags_map() {
        static std::map<const RTTI*, uint32_t> map;
        return map;
    }
};

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
} // cxl

#define RTTI_BASE(CLASSTYPE)                                                       \
    public:                                                                        \
        static const cxl::RTTI* _RTTI()  {                                         \
            static cxl::RTTI s_RTTI(#CLASSTYPE, nullptr);                          \
            return &s_RTTI;                                                        \
        }                                                                          \
        virtual const cxl::RTTI* getRTTI() const {                                 \
             return CLASSTYPE::_RTTI();                                            \
        }                                                                          \
        template <typename T>                                                      \
        T* castTo() const {                                                        \
            return getRTTI()->isTypeOf(T::_RTTI()) ? (T*)this : nullptr;           \
        }                                                                          \
        template <typename T>                                                      \
        bool isTypeOf()	const {                                                    \
            return getRTTI()->isTypeOf(T::_RTTI());                                \
        }                                                                          \
        template <typename T>                                                      \
        bool isType() const {                                                      \
            return getRTTI()->isType(T::_RTTI());                                  \
        }                                                                          \

#define RTTI_DERIVED(CLASSTYPE, BASETYPE)                                          \
    public:                                                                        \
        static const cxl::RTTI *_RTTI() {                                          \
            static cxl::RTTI s_RTTI(#CLASSTYPE, BASETYPE::_RTTI());                \
            return &s_RTTI;                                                        \
        }                                                                          \
        const cxl::RTTI *getRTTI() const override {                                \
            return CLASSTYPE::_RTTI();                                             \
        }                                                                          \
        template <typename T>                                                      \
        T* castTo() const {                                                        \
            return getRTTI()->isTypeOf(T::_RTTI()) ? (T*)this : NULL;              \
        }                                                                          \
        template <typename T>                                                      \
        bool isTypeOf() const {                                                    \
            return getRTTI()->isTypeOf(T::_RTTI());                                \
        }                                                                          \
        template <typename T>                                                      \
        bool isType() const {                                                      \
            return getRTTI()->isType(T::_RTTI());                                  \
        }                                                                          \

#define RTTI_DERIVED_TEMPLATE(CLASSTYPE, TEMPLATETYPE, BASETYPE)                   \
     public:                                                                       \
         static const cxl::RTTI *_RTTI() {                                         \
            std::string name = std::string(#CLASSTYPE) + "<";                      \
            name += TEMPLATETYPE::_RTTI()->class_name() + ">";                     \
            static cxl::RTTI s_RTTI(name, BASETYPE::_RTTI());                      \
            return &s_RTTI;                                                        \
         }                                                                         \
         const cxl::RTTI *getRTTI() const override {                               \
             return CLASSTYPE::_RTTI();                                            \
         }                                                                         \
         template <typename T>                                                     \
         T* castTo() const {                                                       \
             return getRTTI()->isTypeOf(T::_RTTI()) ? (T*)this : NULL;             \
         }                                                                         \
         template <typename T>                                                     \
         bool isTypeOf() const {                                                   \
             return getRTTI()->isTypeOf(T::_RTTI());                               \
         }                                                                         \
         template <typename T>                                                     \
         bool isType() const {                                                     \
             return getRTTI()->isType(T::_RTTI());                                 \
         }                                                                         \

#endif // RTTI_HPP_

