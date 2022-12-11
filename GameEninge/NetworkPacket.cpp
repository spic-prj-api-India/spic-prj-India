#include "NetworkPacket.hpp"
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <sstream>      // std::istringstream
#include <iostream>     // std::ios, std::istream, std::cout
#include <fstream>      // std::filebuf
#include <chrono>
#include "ConvertListToBytes.hpp"

spic::NetworkPacket::NetworkPacket() : timeSpan{ duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() }
{
}

spic::NetworkPacket::NetworkPacket(const std::string& name, const MessageType& typeMessage)
    : name{ name }, typeMessage{ typeMessage }, timeSpan{ duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() }
{
}

spic::NetworkPacket::NetworkPacket(const std::string& name, const MessageType& typeMessage, std::map<std::string, std::string> data)
    : name{ name }, typeMessage{ typeMessage }, data{ data }, timeSpan{ duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() }
{
}

std::stringstream spic::NetworkPacket::Serialize() const
{
    std::string temp = this->name  + '§' + std::to_string(this->timeSpan) + '§' + std::to_string(this->typeMessage) + '§';


    temp += spic::internal::networking::encode_map(this->data);
    temp += '~';

    return std::stringstream(temp);
}

void spic::NetworkPacket::Deserialize(const std::string& in)
{
    std::vector<std::string> strs;
    boost::split(strs, in, boost::is_any_of("§"));

    this->name = strs[0];
    this->timeSpan = std::stoull(strs[1].c_str(), nullptr, 10);
    this->typeMessage = MessageType(std::stoi(strs[2].c_str()));
    this->data = spic::internal::networking::decode_map<std::string, std::string>(strs[3]);
}
