#include <memory>
#include "ForceDriven.hpp"
#include <Flocking.hpp>
#include <Scene.hpp>
#include <BoxCollider.hpp>
#include <Steering.hpp>
#include <SocketUDPExtension.hpp>
#include <GameEngine.hpp>
#include <PhysicsExtension1.hpp>
#include "Persistable.hpp"
#include <Button.hpp>

class MouseListener : public spic::IMouseListener {
	void OnMouseMoved() override
	{
		std::cout << "moved" << std::endl;
	}
	void OnMousePressed() override
	{
		std::cout << "pressed" << std::endl;
	}
};

int main() {
	std::shared_ptr<spic::IMouseListener> mouseListener = std::make_shared<MouseListener>();
	spic::input::Subscribe(spic::input::MouseButton::LEFT, mouseListener);
}