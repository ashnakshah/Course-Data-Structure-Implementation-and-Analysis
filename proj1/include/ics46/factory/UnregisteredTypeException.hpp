// UnregisteredTypeException.hpp
//
// ICS 46 Spring 2016
// ICS 46 Library
//
// An exception thrown by DynamicFactories when an attempt is made to create
// an object using an unregistered type.  For example, if the type Student
// hasn't previously been registered with DynamicFactory<Person>, this call
// would throw an UnregisteredTypeException.
//
//     ics46::factory::DynamicFactory<Person>::instance().make<Student>();

#ifndef UNREGISTEREDTYPEEXCEPTION_HPP
#define UNREGISTEREDTYPEEXCEPTION_HPP

#include <typeinfo>



namespace ics46 { namespace factory
{
    class UnregisteredTypeException
    {
    public:
        UnregisteredTypeException(const std::type_info& unregisteredType)
            : unregisteredType_{unregisteredType}
        {
        }

        const std::type_info& unregisteredType() { return unregisteredType_; }

    private:
        const std::type_info& unregisteredType_;
    };
} }



#endif // UNREGISTEREDTYPEEXCEPTION_HPP

