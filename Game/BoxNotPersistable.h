#pragma once
#include <GameObject.hpp>
#include "Persistable.hpp"

class BoxNotPersistable : public spic::GameObject
{
public:
	BoxNotPersistable();
	BoxNotPersistable(const std::string& name, const spic::Point& position, const float feelerLength = 20.0f);
	void SetAttributes(const spic::Point& position);
private:
	float feelerLength;
};