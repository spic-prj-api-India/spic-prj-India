#ifndef SOCKETSCRIPT_H_
#define SOCKETSCRIPT_H_

#include <iostream>
#include "GameObject.hpp"
#include "Component.hpp"
#include "INetworkExtension.hpp"
#include "NetworkPacket.hpp"

namespace spic {

    /**
     * @brief A component representing a rigid body.
     */
    class SocketScript : public Component {
    public:
        /**
         * @brief Adds a socket to the SocketScript
         * @param socketTypname 
        */
        void AddSocket(std::weak_ptr<spic::extensions::INetworkExtension> socketType);

        /**
         * @brief Creates a new message and calls SendPacket at the end
         * @param entity 
        */
        virtual void Send(std::shared_ptr<spic::GameObject> entity) = 0;

        /**
         * @brief Calls the CreateEntity for createMessage, Calls DestroyEntity for destroyMessages, Calls SyncEntity
         * @param packet 
         * @param entity 
        */
        void Retrieve(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity);
        

        /**
         * @brief Writes own code of creating an entity
         * @param packet 
         * @param entity 
        */
        virtual void CreateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) = 0;

        /**
         * @brief Writes own code for destroying an entiy
         * @param packet 
         * @param entityy 
        */
        virtual void DestroyEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) = 0;

        /**
         * @brief Writes own code for syncing an entity
         * @param packet 
         * @param entity 
        */
        virtual void SyncEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) = 0;

        /**
         * @brief Writes own code for updating an entity
         * @param packet 
         * @param entity 
        */
        virtual void UpdateEntity(const spic::NetworkPacket* packet, std::shared_ptr<spic::GameObject> entity) = 0;

        /**
         * @brief Gets update packet with only an update of the transform of a gameobject.
         * @details Only transform gets added
         * @param gameobject
         * @return
        */
        spic::NetworkPacket PositionPacket(const spic::GameObject* gameobject) const;

        /**
         * @brief Updates the position of an gameobject with children included
         * @param packet
         * @param gameobject
        */
        void UpdatePosition(const spic::NetworkPacket* packet, spic::GameObject* gameobject) const;

        /**
         * @brief Removes a gameobject from the registration
         * @param name Name of entity that will be removed
        */
        void RemoveEntity(const std::string& name);

        /**
         * @brief Sends the network packet to the included socket;
         * @param packet
        */
        void SendPacket(const spic::NetworkPacket& packet);

        /**
         * @brief Adds new gameobject to the registration
         * @param entity
        */
        void RegisterNewEntity(std::shared_ptr<spic::GameObject> entity) const;
    private:
        std::weak_ptr<spic::extensions::INetworkExtension> socket;
    };
}
#endif // SOCKETSCRIPT_H_