#include "Persistable.hpp"

using namespace spic;

Persistable::Persistable(GameObject* gameObject) : gameObject{ gameObject }
{}

std::map<std::string, std::function<std::string()>> Persistable::SaveProperties()
{
	if (gameObject == nullptr)
		return {};
	const auto& transform = gameObject->Transform();
	return {
		{"name", [this]() { return gameObject->Name(); }},
		{"tag", [this]() { return gameObject->Tag(); }},
		{"active", [this]() { return std::to_string(gameObject->Active()); }},
		{"layer", [this]() { return  std::to_string(gameObject->Layer()); }},
		{"pos_x", [transform]() { return std::to_string(transform->position.x); }},
		{"pos_y", [transform]() { return std::to_string(transform->position.y); }},
		{"rotation", [transform]() { return std::to_string(transform->rotation); }},
		{"scale", [transform]() { return std::to_string(transform->scale); }},
		{"dont_destroy_on_load", [this]() { return std::to_string(gameObject->DontDestroyOnLoad()); }}
	};
}

std::map<std::string, std::function<void(const std::string&)>> Persistable::LoadProperties()
{
	if (gameObject == nullptr)
		return {};
	const auto& transform = gameObject->Transform();
	return {
		{"name", [this](const std::string& name) { gameObject->Name(name); }},
		{"tag", [this](const std::string& tag) { gameObject->Tag(tag); }},
		{"active", [this](const std::string& active) { gameObject->Active(std::stoi(active)); }},
		{"layer", [this](const std::string& layer) { gameObject->Layer(std::stoi(layer)); }},
		{"pos_x", [transform](const std::string& pos_x) { transform->position.x = std::stof(pos_x); }},
		{"pos_y", [transform](const std::string& pos_y) { transform->position.y = std::stof(pos_y); }},
		{"rotation", [transform](const std::string& rotation) { transform->rotation = std::stof(rotation); }},
		{"scale", [transform](const std::string& scale) { transform->scale = std::stof(scale); }},
		{"dont_destroy_on_load", [this](const std::string& dont_destroy_on_load) { gameObject->DontDestroyOnLoad(std::stoi(dont_destroy_on_load)); }},
	};
}