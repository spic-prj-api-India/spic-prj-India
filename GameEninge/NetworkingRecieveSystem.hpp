#ifndef NETWORKINGREVIECESYSTEM_H_
#define NETWORKINGREVIECESYSTEM_H_

#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"
#include "INetworkExtension.hpp"

/**
* @brief A system that calls all physics extensions and triggers collision script methods
*/
namespace spic::internal::systems {
    class NetworkingRecieveSystem :
        public spic::systems::ISystem
    {
    public:
        NetworkingRecieveSystem();

        /**
        * @brief Initiliazes system
        * @spicapi
        */
        void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

        /**
        * @brief Sends message to relevant GameObject
        * @spicapi
        */
        void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;
       
    private:
        std::vector<std::weak_ptr<spic::INetworkExtension>> sockets;
    };
}

#endif // PHYSICSSYSTEM_H_
