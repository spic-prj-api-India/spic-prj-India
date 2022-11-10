#ifndef PHYSICSSYSTEM_H_
#define PHYSICSSYSTEM_H_

#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"

namespace systems {
    class PhysicsSystem :
        public ISystem
    {
    public:
        PhysicsSystem();

        void Reset() const;
        void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) const;

        void OnEnter(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) const;
        void OnExit(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) const;
        void OnStay(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider) const;
    private:
        std::vector<std::shared_ptr<spic::GameObject>> GetPhysicsEntities(std::vector<std::shared_ptr<spic::GameObject>> entities) const;
    };
}

#endif // PHYSICSSYSTEM_H_