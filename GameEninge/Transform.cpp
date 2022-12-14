#include "Transform.hpp"
#include <vector>
#include <boost/algorithm/string.hpp>

std::stringstream spic::Transform::Serialize() const
{
    std::string temp = std::to_string(this->position.x) + ' ' + std::to_string(this->position.y) + ' ' + std::to_string(this->rotation) + ' ' + std::to_string(this->scale);
    return std::stringstream(temp);
}

void spic::Transform::Deserialize(const std::string& in)
{
    std::vector<std::string> strs;
    boost::split(strs, in, boost::is_any_of(" "));

    this->position.x = std::stof(strs[0]);
    this->position.y = std::stof(strs[1]);
    this->rotation = std::stof(strs[2]);
    this->scale = std::stof(strs[3]);
}
