#ifndef NETWORKINGSENDSYSTEM_H_
#define NETWORKINGSENDSYSTEM_H_

#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"
#include "INetworkExtension.hpp"


namespace spic::internal::systems 
{
    /**
     * @brief A system sends all bufferd data
     */
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
        std::vector<std::weak_ptr<spic::extensions::INetworkExtension>> sockets;
    };
}

#endif // NETWORKINGSENDSYSTEM_H_