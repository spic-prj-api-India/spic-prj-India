#ifndef NETWORKINGRECEIVESYSTEM_H_
#define NETWORKINGRECEIVESYSTEM_H_

#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"
#include "INetworkExtension.hpp"


namespace spic::internal::systems {

    /**
     * @brief A system that retrieves all info from an socket and processes it
     */
    class NetworkingReceiveSystem :
        public spic::internal::systems::ISystem
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