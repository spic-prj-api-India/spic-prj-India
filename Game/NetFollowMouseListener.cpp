#include "NetFollowMouseListener.h"
#include "Input.hpp"
#include <Steering.hpp>

NetFollowMouseListener::NetFollowMouseListener(spic::Point& targetPosition) : target{ targetPosition }
{
}

void NetFollowMouseListener::OnMouseMoved() {
	const spic::Point mousePosition = spic::input::MousePosition();
	this->target.x = mousePosition.x;
	this->target.y = mousePosition.y;
}

void NetFollowMouseListener::OnMouseClicked() {

}
void NetFollowMouseListener::OnMousePressed() {

}
void NetFollowMouseListener::OnMouseReleased() {

}