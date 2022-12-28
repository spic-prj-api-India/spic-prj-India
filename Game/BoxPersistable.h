#pragma once
#include <GameObject.hpp>
#include "Persistable.hpp"

class BoxPersistable : public spic::GameObject, public spic::Persistable
{
public:
	BoxPersistable();
	BoxPersistable(const std::string& name, const spic::Point& position, const float feelerLength = 20.0f);
	void SetAttributes(const spic::Point& position);

	virtual std::map<std::string, spic::SaveFunction> SaveProperties() override;
	virtual std::map<std::string, spic::LoadFunction> LoadProperties() override;
private:
	float feelerLength;
};