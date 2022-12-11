#ifndef NETWORKPACKAGE_H_
#define NETWORKPACKAGE_H_
#include <string>
#include <map>
#include <sstream>
#include <chrono>
namespace spic
{
    /**
     * @brief What type of message
    */
    enum MessageType : int
    {
        CREATE = 0,
        UPDATE = 1,
        DESTROY = 2,
        SYNC = 3,
    };

    /**
     * @brief An network package
     * @details The data in this message cannot contains the characters '§' and '~'.
     * Timespan gets created by creating of this object. Do not touch unless you know what you are doing. 
    */
    struct NetworkPacket
    {
        /**
         * @brief Name of a Gameobject
        */
        std::string name;

        /**
         * @brief when the message was sent
        */
        long long timeSpan;

        /**
         * @brief type of message
        */
        MessageType typeMessage;

        /**
         * @brief Data in message
        */
        std::map<std::string,std::string> data;

        /**
         * @brief Default constructor
        */
        NetworkPacket();

        /**
        * @brief Creates an object with all parameters except data
        * @param name
        * @param type
        * @param typeMessage
       */
        NetworkPacket(const std::string& name, const MessageType& typeMessage);

        /**
         * @brief Creates an object with all parameters
         * @param name 
         * @param type 
         * @param typeMessage 
         * @param data 
        */
        NetworkPacket(const std::string& name, const MessageType& typeMessage, std::map<std::string, std::string> data);

        std::stringstream Serialize() const;

        void Deserialize(const std::string& in);
    };
}
#endif // NETWORKPACKAGE_H_