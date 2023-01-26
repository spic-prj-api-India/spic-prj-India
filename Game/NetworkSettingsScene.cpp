#include "NetworkSettingsScene.h"
#include <Button.hpp>
#include "GameEngine.hpp"
#include <Text.hpp>
#include "KeyListener.h"
#include <Input.hpp>
#include "GameScene.h"
#include "DataHandler.hpp"
#include "Text.hpp"
#include <SocketUDPExtension.hpp>

using namespace spic;

NetworkSettingsScene::NetworkSettingsScene() : Scene(), ip{""}
{
	SetCamera();
	SetContents();
	RestoreSettings();
}

void NetworkSettingsScene::SetCamera()
{
	std::unique_ptr<spic::Camera> camera = std::make_unique<spic::Camera>();
	camera->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 0.0f), 0.0f, 1.0f));
	camera->BackgroundColor(spic::Color::magenta());
	camera->BackgroundImage("assets/textures/backgrounds/bg2.png");
	Camera(std::move(camera));
}

void NetworkSettingsScene::SetContents()
{
	auto titleText = std::make_shared<spic::Text>(1250.0f, 900.0f
		, "Network settings"
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());

	titleText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 100.0f), 0.0f, 1.0f));
	AddContent(titleText);

	AddButton("menuBtn", "Back to settings", [this]() {
		GameEngine::GetInstance()->LoadSceneByName("settings");
		}, -50.0f);

	ipText = std::make_shared<spic::Text>(1250.0f, 900.0f
		, ip
		, ""
		, 50
		, spic::Alignment::CENTER
		, spic::Color::white());
	
	ipText->Transform(std::make_shared<spic::Transform>(spic::Point(0.0f, 375.0f), 0.0f, 1.0f));
	AddContent(ipText);
	typeListener = std::make_shared<InputTypeListener>(ipText, *&ip);
	input::Subscribe(input::KeyCode::NUMBER_1_AND_EXCLAMATION, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_2_AND_AT, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_3_AND_HASHMARK, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_4_AND_DOLLAR, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_5_AND_PERCENTAGE, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_6_AND_CARET, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_7_AND_AMPERSAND, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_8_AND_ASTERISK, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_9_AND_OPENING_PARENTHESIS, typeListener);
	input::Subscribe(input::KeyCode::NUMBER_0_AND_CLOSING_PARENTHESIS, typeListener);
	input::Subscribe(input::KeyCode::DOT_AND_GREATER_THAN_SIGN, typeListener);
	input::Subscribe(input::KeyCode::BACKSPACE, typeListener);

	AddButton("saveBtn", "Save", [this]() {
		spic::DataHandler dataHandler = spic::DataHandler("network_settings");
		settings["opponent_ip"] = this->ip;
		dataHandler.AddSettings(settings);
		dataHandler.Save();
		auto networkExtensions = GameEngine::GetInstance()->GetExtensions<extensions::INetworkExtension>();
		for (const auto& extension : networkExtensions)
			if (const auto& networkExtension = extension.lock())
				networkExtension->InitSender(this->ip, 13252);
		}, 230.0f);
}

void NetworkSettingsScene::RestoreSettings()
{
	spic::DataHandler dataHandler = spic::DataHandler("network_settings");
	dataHandler.LoadSettings(settings);
	this->ip = settings["opponent_ip"];
	this->ipText->_Text(this->ip);
	
}

void NetworkSettingsScene::AddButton(const std::string& name, const std::string& text, std::function<void()> callback, const float offset)
{
	auto button = std::make_shared<spic::Button>(250.0f, 100.0f, text, spic::Color::white(), "assets/textures/buttons/Button22.png");
	button->Name(name);
	button->Transform(std::make_shared<spic::Transform>(spic::Point(500.0f, 260.0f + offset), 0.0f, 1.0f));
	auto textTransform = button->GetChild<spic::Text>()->Transform();
	textTransform->position.y = 35.0f;
	button->OnClick(callback);
	AddContent(button);
}

spic::Scene* NetworkSettingsScene::Start()
{
	spic::input::UnSubscribeAll();
	NetworkSettingsScene* a = new NetworkSettingsScene();
	return a;
}