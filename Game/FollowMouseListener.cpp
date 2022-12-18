#include "FollowMouseListener.h"
#include "Input.hpp"

FollowMouseListener::FollowMouseListener()
{
	const spic::Point mousePosition = spic::Input::MousePosition();
	target = std::make_unique<spic::Point>(mousePosition.x, mousePosition.y);
	followers;
}

void FollowMouseListener::AddFollower(std::shared_ptr<spic::ForceDriven> follower)
{
	//follower->AddTarget(spic::SteeringBehaviour::FLEE, *target.get(), 1.0f);
	follower->AddTarget(spic::SteeringBehaviour::SEEK, *target.get(), 1.0f);
	//follower->AddTarget(spic::SteeringBehaviour::ARRIVAL, *target.get(), 1.0f);
	this->followers.emplace_back(std::move(follower));
}

void FollowMouseListener::OnMouseMoved() {
	const spic::Point mousePosition = spic::Input::MousePosition();
	this->target->x = mousePosition.x;
	this->target->y = mousePosition.y;
}

void FollowMouseListener::OnMouseClicked() {

}
void FollowMouseListener::OnMousePressed() {

}
void FollowMouseListener::OnMouseReleased() {

}