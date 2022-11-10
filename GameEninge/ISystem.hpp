#ifndef ISYSTEM_H_
#define ISYSTEM_H_

#include <iostream>
#include <vector>
#include "GameObject.hpp"
class ISystem
{
public:
	virtual void Update(std::vector<std::shared_ptr<spic::GameObject>> entities) const = 0;
private:
};

#endif // ISYSTEM_H_