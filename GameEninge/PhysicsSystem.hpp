#pragma once
#include <map>
#include "ISystem.hpp"
#include "IEngineExtension.hpp"

namespace systems {
    class PhysicsSystem :
        public ISystem
    {
    public:
        PhysicsSystem();
        void Reset();
        void Update(std::vector<std::shared_ptr<spic::GameObject>> entities);
        void OnEnter(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider);
        void OnExit(const std::shared_ptr<spic::GameObject>& entity, const std::shared_ptr<spic::Collider>& collider);
    private:
        std::vector<std::shared_ptr<spic::GameObject>> GetPhysicsEntities(std::vector<std::shared_ptr<spic::GameObject>> entities);
        void OnStay(std::vector<std::shared_ptr<spic::GameObject>> entities);
    private:
        std::map<std::string, std::vector<std::shared_ptr<spic::Collider>>> onStays;
    };
}