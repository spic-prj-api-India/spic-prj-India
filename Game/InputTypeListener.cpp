#include "InputTypeListener.h"

#include "KeyListener.h"
#include <iostream>

InputTypeListener::InputTypeListener(std::shared_ptr<spic::Text> inputField, std::string& text) :
	inputField{ std::move(inputField) }, text{ text }
{
}

void InputTypeListener::OnKeyPressed()
{
	if(spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_1_AND_EXCLAMATION))
		text += '1';
	else if(spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_2_AND_AT))
		text += '2';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_3_AND_HASHMARK))
		text += '3';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_4_AND_DOLLAR))
		text += '4';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_5_AND_PERCENTAGE))
		text += '5';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_6_AND_CARET))
		text += '6';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_7_AND_AMPERSAND))
		text += '7';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_8_AND_ASTERISK))
		text += '8';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_9_AND_OPENING_PARENTHESIS))
		text += '9';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::NUMBER_0_AND_CLOSING_PARENTHESIS))
		text += '0';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::DOT_AND_GREATER_THAN_SIGN))
		text += '.';
	else if (spic::input::GetKeyDown(spic::input::KeyCode::BACKSPACE) && text.size() > 0)
		text.pop_back();
	inputField->_Text(text);
}
void InputTypeListener::OnKeyReleased()
{
}