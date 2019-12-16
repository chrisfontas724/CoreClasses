# RTTI
Basic header-only interface for simple C++ projects that require runtime type information (RTTI), factories or the service design pattern.

Just drop these headers into your project and begin using.



# Example Usage (Creating Factory Service)


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
