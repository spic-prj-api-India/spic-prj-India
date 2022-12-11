#pragma once
#include <sstream>

namespace spic {

    struct Serializer
    {
        virtual std::stringstream Serialize() const = 0;

        virtual void Deserialize(const std::string& in) = 0;
    };
}