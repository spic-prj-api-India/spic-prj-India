#ifndef NETWORKINGRECEIVESYSTEM_H_
#define NETWORKINGRECEIVESYSTEM_H_

#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"
#include "INetworkExtension.hpp"

/**
* @brief A system that calls all physics extensions and triggers collision script methods
*/
namespace spic::internal::systems {
    class NetworkingReceiveSystem :
        public spic::systems::ISystem
    {
    public:
        NetworkingReceiveSystem();

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
        std::vector<std::weak_ptr<spic::extensions::INetworkExtension>> sockets;
    };
}

#endif // NETWORKINGRECEIVESYSTEM_H_