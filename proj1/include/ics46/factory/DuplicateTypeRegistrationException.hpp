// DuplicateTypeRegistrationException.hpp
//
// ICS 46 Spring 2016
// ICS 46 Library
//
// Exception that is thrown when attempting to register the same type with
// the same DynamicFactory twice.  Since registration is primarily done
// using a global macro call, this will predominantly be thrown at startup.

#ifndef DUPLICATETYPEREGISTRATIONEXCEPTION_HPP
#define DUPLICATETYPEREGISTRATIONEXCEPTION_HPP

#include <typeinfo>



namespace ics46 { namespace factory
{
    class DuplicateTypeRegistrationException
    {
    public:
        DuplicateTypeRegistrationException(const std::type_info& duplicateType)
            : duplicateType_(duplicateType)
        {
        }

        const std::type_info& duplicateType() { return duplicateType_; }

    private:
        const std::type_info& duplicateType_;
    };
} }



#endif // DUPLICATETYPEREGISTRATIONEXCEPTION_HPP

