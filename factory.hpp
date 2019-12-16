// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "core/rtti/rtti.hpp"
#include <map>

namespace cxl {
    template<typename T>
    class Factory {
    public:
        
        class Generator {
        public:
            Generator() {}
            virtual ~Generator() {}
            virtual T *generate() const = 0;
        };
        
        template <typename GENERATE_TYPE>
        class GeneratorT : public Generator {
        public:
            T* generate() const override { return dynamic_cast<T*>(new GENERATE_TYPE); }
        };
        
    public:
        
        // Register class generator with this factory.
        template <typename GENERATE_TYPE>
        void registerClass() {
            static GeneratorT<GENERATE_TYPE> s_instance;
            registry_[GENERATE_TYPE::_RTTI()->class_id()] = &s_instance;
            class_names_map_[GENERATE_TYPE::_RTTI()->class_id()] = GENERATE_TYPE::_RTTI()->class_name();
        }
        
        template<typename GENERATE_TYPE>
        bool isRegistered() const {
            return registry_.count(GENERATE_TYPE::_RTTI()->class_id());
        }
        
        bool isRegistered(uint32_t class_id) const {
            return registry_.count(class_id);
        }
        
        bool isRegistered(const std::string& class_name) const {
            return registry_.count(hashClass(class_name));
        }
        
        T* generate(uint32_t class_id) {
            if (registry_.count(class_id)) {
                const Generator* generator = registry_[class_id];
                return generator->generate();
            }
            return nullptr;
        }
        
        T* generate(const std::string& name) {
	        uint32_t class_id = utils::simpleHash(name);
            if (registry_.count(class_id)) {
                const Generator* generator = registry_[class_id];
                return generator->generate();
            }
            return nullptr;
        }
        
        uint32_t hashClass(const std::string& class_name) {
            return (uint32_t)utils::simpleHash(class_name);
        }
        
        const std::string& class_name(uint32_t type) {
            return class_names_map_[type];
        }
        
        const std::map<uint32_t, std::string>& class_names_map() const {
            return class_names_map_;
        }
        
    private:
        std::map<uint32_t, Generator*> registry_;
        std::map<uint32_t, std::string> class_names_map_;
    };
} // cxl

#endif // FACTORY_HPP_
