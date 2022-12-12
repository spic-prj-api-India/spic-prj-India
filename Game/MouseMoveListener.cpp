#include "FollowMouseListener.h"
#include "Input.hpp"

FollowMouseListener::FollowMouseListener()
{
	followers;
}

void FollowMouseListener::AddFollower(const std::shared_ptr<spic::ForceDriven>& follower)
{
	this->followers.emplace_back(follower);
}

void FollowMouseListener::OnMouseMoved() {
	const spic::Point mousePosition = spic::Input::MousePosition();
	for (const auto& follower : followers) {
		follower->Target(mousePosition, 1.0f);
	}
}
void FollowMouseListener::OnMouseClicked() {
	
}
void FollowMouseListener::OnMousePressed() {
	
}
void FollowMouseListener::OnMouseReleased() {
	
}