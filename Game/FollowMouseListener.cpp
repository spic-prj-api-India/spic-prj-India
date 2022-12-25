#include "FollowMouseListener.h"
#include "Input.hpp"
#include <Steering.hpp>
#include <DataHandler.hpp>

FollowMouseListener::FollowMouseListener()
{
	const spic::Point mousePosition = spic::input::MousePosition();
	target = std::make_unique<spic::Point>(mousePosition.x, mousePosition.y);
}

void FollowMouseListener::AddFollower(std::shared_ptr<spic::ForceDriven> follower)
{
	const auto& steering = follower->GetComponent<spic::Steering>();
	std::map<std::string, std::string> settings;
	spic::DataHandler dataHandler = spic::DataHandler("flock_settings");
	dataHandler.LoadSettings(settings);
	if (std::stoi(settings["use_flee"]))
		steering->AddTarget(spic::TargetBehaviour::FLEE, *target.get(), 1.0f);
	if (std::stoi(settings["use_seek"]))
		steering->AddTarget(spic::TargetBehaviour::SEEK, *target.get(), 1.0f);
	if (std::stoi(settings["use_arrival"]))
		steering->AddTarget(spic::TargetBehaviour::ARRIVAL, *target.get(), 1.0f);
}

void FollowMouseListener::OnMouseMoved() {
	const spic::Point mousePosition = spic::input::MousePosition();
	this->target->x = mousePosition.x;
	this->target->y = mousePosition.y;
}

void FollowMouseListener::OnMouseClicked() {

}
void FollowMouseListener::OnMousePressed() {

}
void FollowMouseListener::OnMouseReleased() {

}