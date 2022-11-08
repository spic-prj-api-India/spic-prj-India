#pragma once
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
    };
}