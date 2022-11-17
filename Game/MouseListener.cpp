#include "MouseListener.h"
#include <iostream>
void MouseListener::OnMouseMoved() {
	std::cout << "Mouse moved" << std::endl;
}
void MouseListener::OnMouseClicked() {
	std::cout << "Mouse clicked" << std::endl;
}
void MouseListener::OnMousePressed() {
	std::cout << "Mouse pressed" << std::endl;
}
void MouseListener::OnMouseReleased() {
	std::cout << "Mouse released" << std::endl;
}