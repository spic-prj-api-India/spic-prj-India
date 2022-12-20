#pragma once
#include <iostream>
#include <BehaviourScript.hpp>
#include <GameObject.hpp>

class CollisionDetectionScript :
	public spic::BehaviourScript {
public:
    virtual void OnTriggerEnter2D(const spic::Collider& collider) override;
    virtual void OnTriggerExit2D(const spic::Collider& collider) override;
    virtual void OnTriggerStay2D(const spic::Collider& collider) override;
};