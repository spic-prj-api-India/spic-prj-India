#pragma once
#include <iostream>
#include <vector>
#include "GameObject.hpp"
class ISystem
{
public:
	virtual void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) = 0;
private:
};