#ifndef NETWORKINGSENDSYSTEM_H_
#define NETWORKINGSENDSYSTEM_H_

#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"
#include "INetworkExtension.hpp"

/**
* @brief A system that calls all physics extensions and triggers collision script methods
*/
namespace spic::internal::systems {
    class NetworkingSendSystem :
        public spic::systems::ISystem
    {
    public:
        NetworkingSendSystem();

        /**
        * @brief Initiliazes system
        * @spicapi
        */
        void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

        /**
        * @brief Sends message to relevant gameobject
        * @spicapi
        */
        void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

    private:
        std::vector<std::weak_ptr<spic::INetworkExtension>> sockets;
    };
}

#endif // NETWORKINGSENDSYSTEM_H_

