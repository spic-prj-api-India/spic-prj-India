#include "FollowMouseListener.h"
#include "Input.hpp"
#include <Steering.hpp>

FollowMouseListener::FollowMouseListener(spic::Point& targetPosition) : target{ targetPosition }
{
}

void FollowMouseListener::OnMouseMoved() {
	const spic::Point mousePosition = spic::input::MousePosition();
	this->target.x = mousePosition.x;
	this->target.y = mousePosition.y;
}

void FollowMouseListener::OnMouseClicked() {

}
void FollowMouseListener::OnMousePressed() {

}
void FollowMouseListener::OnMouseReleased() {

}