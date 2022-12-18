#pragma once
#include <GameObject.hpp>
#include "Persistable.hpp"

class Box : public spic::GameObject, public spic::Persistable
{
public:
	Box();
	Box(const std::string& name, const spic::Point& position, const float feelerLength = 20.0f);
	void SetAttributes(const spic::Point& position);

	virtual std::map<std::string, std::function<std::string()>> SaveProperties() override;
	virtual std::map<std::string, std::function<void(const std::string&)>> LoadProperties() override;
private:
	float feelerLength;
};