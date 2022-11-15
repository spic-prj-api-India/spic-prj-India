#include "KeyListener.h"
#include <iostream>

void KeyListener::OnKeyPressed() {
	std::cout << "A Key pressed" << std::endl;
}
void KeyListener::OnKeyReleased() {
	std::cout << "A Key released" << std::endl;
}