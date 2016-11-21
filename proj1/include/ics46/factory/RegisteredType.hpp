// RegisteredType.hpp
//
// ICS 46 Spring 2016
// ICS 46 Library
//
// A RegisteredType<BaseType> describes a type registered with a
// DynamicFactory<BaseType>.  A RegisteredType has these properties:
//
// * A name that uniquely identifies it and can be used to create
//   an object of that type without having access to the actual type
// * A type_info object that describes the C++ type
// * A creation function that is used to create objects of that type

#ifndef REGISTEREDTYPE_HPP
#define REGISTEREDTYPE_HPP

#include <functional>
#include <memory>
#include <string>
#include <typeinfo>



namespace ics46 { namespace factory
{
    template <typename BaseType>
    class RegisteredType 
    {
    public:
        RegisteredType(
            const std::string& name, const std::type_info& type,
            std::function<std::unique_ptr<BaseType>()> creationFunction)
                : name_{name}, type_{type},
                  creationFunction{creationFunction}
        {
        }

        std::unique_ptr<BaseType> build() const { return creationFunction(); }
        const std::type_info& type() const { return type; }
        const std::string& name() const { return name_; }

    private:
        std::string name_;
        const std::type_info& type_;
        std::function<std::unique_ptr<BaseType>()> creationFunction;
    };
} }



#endif // REGISTEREDTYPE_HPP

