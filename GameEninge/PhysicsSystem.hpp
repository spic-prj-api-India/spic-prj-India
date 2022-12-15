#ifndef PHYSICSSYSTEM_H_
#define PHYSICSSYSTEM_H_

#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"
#include "Collider.hpp"

/**
* @brief A system that calls all physics extensions and triggers collision script methods
*/
namespace spic::internal::systems {
    class PhysicsSystem :
        public spic::systems::ISystem
    {
    public:
        PhysicsSystem();

        /**
        * @brief Resets physics extensions and registers new collision listener
        * @spicapi
        */
        void Reset() const;

        /**
        * @brief Initiliazes system
        * @spicapi
        */
        void Start(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

        /**
        * @brief Calls update method of physics extensions
        * @spicapi
        */
        void Update(std::vector<std::shared_ptr<spic::GameObject>>& entities, Scene& currentScene) override;

        /**
        * @brief Calls OnEnter method in the scripts of the entity
        * @spicapi
        */
        void OnEnter(const std::shared_ptr<spic::GameObject> entity, const std::shared_ptr<spic::Collider> collider) const;

        /**
        * @brief Calls OnExit method in the scripts of the entity
        * @spicapi
        */
        void OnExit(const std::shared_ptr<spic::GameObject> entity, const std::shared_ptr<spic::Collider> collider) const;

        /**
        * @brief Calls OnStay method in the scripts of the entity
        * @spicapi
        */
        void OnStay(const std::shared_ptr<spic::GameObject> entity, const std::shared_ptr<spic::Collider> collider) const;
    private:
        /**
        * @brief Filters all physics entities from entity list
        * @spicapi
        */
        void GetPhysicsEntities(std::vector<std::shared_ptr<spic::GameObject>>& physicsEntities, const std::vector<std::shared_ptr<spic::GameObject>>& entities) const;

        /**
       * @brief Checks if entity has RigidBody or Collider
       * @spicapi
       */
        bool IsPhysicsEntity(const spic::GameObject* entity) const;
    };
}

#endif // PHYSICSSYSTEM_H_