// Copyright 2019 Sic Studios. All rights reserved.
// Use of this source code is governed by our license that can be
// found in the LICENSE file.

#ifndef RTTI_SERVICE_HPP_
#define RTTI_SERVICE_HPP_

#include "rtti/factory.hpp"

namespace cxl {

class IService {
    RTTI_BASE(IService)
public:
        
    // Performs any initialization you need.
    virtual bool onStartup() = 0;
        
    // Performs any per-frame processing for this service.
    virtual bool onUpdate() = 0;
        
    // Frees any non-essential memory and pauses any background processing.
    virtual bool onPause() = 0;
        
    // Resume operation halted by a prior call to onPause().
    virtual bool onResume() = 0;
        
    // Shuts down the service.
    virtual bool onShutdown() = 0;
        
    // Resets the service data.
    virtual bool onReset() = 0;
};

template<typename S>
class Service : public IService {
     RTTI_DERIVED_TEMPLATE(Service, S, IService)
public:
    // |IService|
    virtual bool onStartup() override { return true; }
        
    // |IService|
    virtual bool onUpdate() override { return true; }
        
    // |IService|
    virtual bool onPause() override { return true; }
        
    // |IService|
    virtual bool onResume() override { return true; }
        
    // |IService|
    virtual bool onShutdown() override { return true; }
        
    // |IService|
    virtual bool onReset() override { return true; }
        
protected:
        
    //friend class Locator;
    Service(){}
};


template<typename F>
class FactoryService : public Service<FactoryService<F>> {
    RTTI_DERIVED_TEMPLATE(FactoryService, F, IService)
public:
        
    bool onStartup() override {
        return true;
    }
        
    template<typename GENERATE_TYPE>
    void registerClass() { factory_.template registerClass<GENERATE_TYPE>(); }
        
    template<typename GENERATE_TYPE>
    bool isRegistered() const { return factory_.template isRegistered<GENERATE_TYPE>(); }
        
    bool isRegistered(uint32_t type) const { return factory_.isRegistered(type); }
    
    F* generate(uint32_t type) { return factory_.generate(type); }
        
    F* generate(const std::string& class_name){ return factory_.generate(class_name); }
        
    template<typename GENERATE_TYPE>
    GENERATE_TYPE* generate() {
        return dynamic_cast<GENERATE_TYPE*>(generate(GENERATE_TYPE::_RTTI()->class_id()));
    }
        
    uint32_t getHash(const std::string& class_name){ return factory_.hashClass(class_name); }
        
    std::string get_class(uint32_t type){ return factory_.getClass(type); }
        
    const std::map<uint32_t, std::string>& registeredClasses() const { return factory_.class_names_map(); }
    
private:
        
    static IService *instantiate() {
        return new FactoryService();
    }
        
    Factory<F> factory_;
};

class Locator {
public:

    static Locator *getInstance() {
        static Locator locator;
        return &locator;
    }

    template<typename T>
    static void registerService(T* service) {
        static std::mutex mutex;
        mutex.lock();
        std::map<uint32_t, IService *> &map = getInstance()->service_hash_;
        uint32_t class_id = T::_RTTI()->class_id();
        map[class_id] = service;
        mutex.unlock();
    }

    template<typename T>
    static T* get() {
        const std::map<uint32_t, IService *> &map = getInstance()->service_hash_;
            
        uint32_t class_id = T::_RTTI()->class_id();
        if (map.count(class_id)) {
            return dynamic_cast<T*>(map.at(class_id)); 
        }
        return nullptr;
    }

    static bool startupServices();
    static bool pauseServices();
    static bool updateServices();
    static bool resetServices();

private:
    std::map<uint32_t, IService *> service_hash_;
};


template<typename S>
class ServiceProvider {
public:
    ServiceProvider() {
     if (!Locator::get<S>()) {
        Locator::registerService<S>(new S());
     }
    }
};

template<typename B, typename D>
class Registrar {
public:
    Registrar() {
        FactoryService<B>* factory = Locator::get<FactoryService<B>>();
        if (factory && !factory->template isRegistered<D>()) {
            factory->template registerClass<D>();
        }
    }
};

inline bool Locator::startupServices() {
    // Loop over all services types
    for (auto &service: getInstance()->service_hash_) {
        bool result = service.second->onStartup(); 
        if (!result)  {
            CXL_LOG(ERROR) << "Could not startup service " << service.second->getRTTI()->class_name();
            return false;
        }
    }
    return true;
}

inline bool Locator::pauseServices() {
    // Loop over all services types
    for (auto &service: getInstance()->service_hash_) {
        bool result = service.second->onPause(); 
        if (!result)  {
            CXL_LOG(ERROR) << "Could not pause service " << service.second->getRTTI()->class_name();
            return false;
        }
    }
    return true;
}

inline bool Locator::updateServices() {
    // Loop over all services types
    for (auto &service: getInstance()->service_hash_) {
        bool result = service.second->onUpdate(); 
        if (!result)  {
            CXL_LOG(ERROR) << "Could not update service " << service.second->getRTTI()->class_name();
            return false;
        }
    }
    return true;
}

inline bool Locator::resetServices() {
    // Loop over all services types
    for (auto &service: getInstance()->service_hash_) {
        bool result = service.second->onReset(); 
        if (!result)  {
            CXL_LOG(ERROR) << "Could not reset service " << service.second->getRTTI()->class_name();
            return false;
        }
    }
    return true;
}

#define DEFINE_SERVICE(CLASS)                                     \
    static cxl::ServiceProvider<CLASS> s_provider##CLASS;         \

#define DEFINE_FACTORY_SERVICE(CLASS)                             \
    typedef cxl::FactoryService<CLASS> CLASS##FactoryService;     \
    DEFINE_SERVICE(CLASS##FactoryService)                         \
                   
#define REGISTER_CLASS(CLASS, BASE)                               \
    static cxl::Registrar<BASE, CLASS> s_registrar##CLASS;        \

} // cxl

#endif // RTTI_SERVICE_HPP_