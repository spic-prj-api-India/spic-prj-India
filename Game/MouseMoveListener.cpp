#include "FollowMouseListener.h"
#include "Input.hpp"

FollowMouseListener::FollowMouseListener()
{
	followers;
}

void FollowMouseListener::AddFollower(const std::shared_ptr<spic::Flock>& follower)
{
	this->followers.emplace_back(follower);
}

void FollowMouseListener::OnMouseMoved() {
	spic::Point mousePosition = spic::Input::MousePosition();
	for (const auto& follower : followers) {
		follower->Target(std::make_unique<spic::Point>(mousePosition));
	}
}
void FollowMouseListener::OnMouseClicked() {
	
}
void FollowMouseListener::OnMousePressed() {
	
}
void FollowMouseListener::OnMouseReleased() {
	
}