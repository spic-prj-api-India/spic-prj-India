#include "BehaviourScript.hpp"


namespace spic {
	void BehaviourScript::GameObject(const std::shared_ptr<spic::GameObject> _gameObject) 
	{
		gameObject = _gameObject;
	}

	void BehaviourScript::OnStart() 
	{
	}

	void BehaviourScript::OnUpdate() 
	{}

	void BehaviourScript::OnTriggerEnter2D(const Collider& collider) 
	{}

	void BehaviourScript::OnTriggerExit2D(const Collider& collider) 
	{}

	void BehaviourScript::OnTriggerStay2D(const Collider& collider) 
	{}
}