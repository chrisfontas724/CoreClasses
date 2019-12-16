# RTTI
Basic header-only interface for simple C++ projects that require runtime type information (RTTI), factories or the service design pattern.

Just drop these headers into your project and begin using.



# Example Usage 1 - Creating Factory Service


    // Create a base class and include the RTTI_BASE macro:
    class Base {
         RTTI_BASE(Base)
    };

    // Define a factory service for the base class with the following macro:
    DEFINE_FACTORY_SERVICE(Base);


    // Now create a derived class that inherits from Base, and include the
    // RTTI_DERIVED macro:
    class Derived : public Base{
        RTTI_DERIVED(Derived, Base)

    };

    // Register the derived class as part of the Base Factory:
    REGISTER_CLASS(Derived, Base)


    // Now your factory is automatically set up and registered with the
    // Locator. You can now simply use the locator to get your factory
    // and begin generating instances of your derived classes. You can
    // use either the name of the class as a string, or use the class's
    // RTTI type:
    auto* instance = cxl::Locator::get<BaseFactoryService>()->generate("Derived");
    auto* instance2 = cxl::Locator::get<BaseFactoryService>()->generate(Derived::_RTTI());


# Example Usage 2 - Creating Generic Service

Create a class that inherits from IService. Use the RTTI_DERIVED macro from
above and call DEFINE_SERVICE underneath. IService comes with several pure virtual functions that need to be overriden as well.

    class MyService : public IService {
        RTTI_DERIVED(MyService, IService)
    public:
        // |IService|
        bool onStartup() override {return true; }
              
        // |IService|
        bool onUpdate() override { return true; }
 
        // |IService|
        bool onPause() override {return true; }
              
        // |IService|
        bool onResume() override {return true; }
              
        // |IService|
        bool onShutdown() override {return true; }
              
        // |IService|
        bool onReset() override {return true; }
    };
    DEFINE_SERVICE(MyService)
    
    
Once your service is defined, it can be managed through the locator. For example, calling the following will cause all your defined serviced to startup:
    
    cxl::Locator::startupServices();
    
If you're creating a game or some other application with a run-loop, you can likewise update your services at a regular interval with the following:
    
    cxl::Locator::updateServices();
