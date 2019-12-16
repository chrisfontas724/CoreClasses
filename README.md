# RTTI
Basic header-only interface for simple C++ projects that require runtime type information (RTTI), factories or the service design pattern.

Just drop these headers into your project and begin using.



# Example Usage (Creating Factory Service)


class Base {
     RTTI_BASE(Base)
};
DEFINE_FACTORY_SERVICE(Base);


class Derived : public Base{
    RTTI_DERIVED(Derived, Base)
};
REGISTER_CLASS(Derived, Base)


cxl::Locator::get<BaseFactoryService>()->generate("Derived");
cxl::Locator::get<BaseFactoryService>()->generate(Derived::_RTTI());
