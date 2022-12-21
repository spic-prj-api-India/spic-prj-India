#include "InputImpl.hpp"
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_events.h>
#pragma warning( pop )

/**
 * @brief Contains the implementation details from the input class.
*/
namespace spic::internal::input::impl 
{
	SDL_Event ev;

	std::vector<SDL_Keycode> ToSDLKeyCodes(spic::input::KeyCode key) 
	{
		switch (key) 
		{
			case spic::input::KeyCode::ERROR_ROLLOVER:
				return {};
			case spic::input::KeyCode::POST_FAIL:
				return {};
			case spic::input::KeyCode::ERROR_UNDEFINED:
				return {};
			case spic::input::KeyCode::A:
				return { SDLK_a };
			case spic::input::KeyCode::B:
				return { SDLK_b };
			case spic::input::KeyCode::C:
				return { SDLK_c };
			case spic::input::KeyCode::D:
				return { SDLK_d };
			case spic::input::KeyCode::E:
				return { SDLK_e };
			case spic::input::KeyCode::F:
				return { SDLK_f };
			case spic::input::KeyCode::G:
				return { SDLK_g };
			case spic::input::KeyCode::H:
				return { SDLK_h };
			case spic::input::KeyCode::I:
				return { SDLK_i };
			case spic::input::KeyCode::J:
				return { SDLK_j };
			case spic::input::KeyCode::K:
				return { SDLK_k };
			case spic::input::KeyCode::L:
				return { SDLK_l };
			case spic::input::KeyCode::M:
				return { SDLK_m };
			case spic::input::KeyCode::N:
				return { SDLK_n };
			case spic::input::KeyCode::O:
				return { SDLK_o };
			case spic::input::KeyCode::P:
				return { SDLK_p };
			case spic::input::KeyCode::Q:
				return { SDLK_q };
			case spic::input::KeyCode::R:
				return { SDLK_r };
			case spic::input::KeyCode::S:
				return { SDLK_s };
			case spic::input::KeyCode::T:
				return { SDLK_t };
			case spic::input::KeyCode::U:
				return { SDLK_u };
			case spic::input::KeyCode::V:
				return { SDLK_v };
			case spic::input::KeyCode::W:
				return { SDLK_w };
			case spic::input::KeyCode::X:
				return { SDLK_x };
			case spic::input::KeyCode::Y:
				return { SDLK_y };
			case spic::input::KeyCode::Z:
				return { SDLK_z };
			case spic::input::KeyCode::NUMBER_1_AND_EXCLAMATION:
				return { SDLK_1, SDLK_EXCLAIM };
			case spic::input::KeyCode::NUMBER_2_AND_AT:
				return { SDLK_2, SDLK_AT };
			case spic::input::KeyCode::NUMBER_3_AND_HASHMARK:
				return { SDLK_3, SDLK_HASH };
			case spic::input::KeyCode::NUMBER_4_AND_DOLLAR:
				return { SDLK_4, SDLK_DOLLAR };
			case spic::input::KeyCode::NUMBER_5_AND_PERCENTAGE:
				return { SDLK_5, SDLK_PERCENT };
			case spic::input::KeyCode::NUMBER_6_AND_CARET:
				return { SDLK_6, SDLK_CARET };
			case spic::input::KeyCode::NUMBER_7_AND_AMPERSAND:
				return { SDLK_7, SDLK_AMPERSAND };
			case spic::input::KeyCode::NUMBER_8_AND_ASTERISK:
				return { SDLK_8, SDLK_ASTERISK };
			case spic::input::KeyCode::NUMBER_9_AND_OPENING_PARENTHESIS:
				return { SDLK_9, SDLK_LEFTPAREN };
			case spic::input::KeyCode::NUMBER_0_AND_CLOSING_PARENTHESIS:
				return { SDLK_0, SDLK_RIGHTPAREN };
			case spic::input::KeyCode::ENTER:
				return { SDLK_KP_ENTER };
			case spic::input::KeyCode::ESCAPE:
				return { SDLK_ESCAPE };
			case spic::input::KeyCode::BACKSPACE:
				return { SDLK_BACKSPACE };
			case spic::input::KeyCode::TAB:
				return { SDLK_TAB };
			case spic::input::KeyCode::SPACE:
				return { SDLK_SPACE };
			case spic::input::KeyCode::MINUS_AND_UNDERSCORE:
				return { SDLK_MINUS, SDLK_UNDERSCORE };
			case spic::input::KeyCode::EQUAL_AND_PLUS:
				return { SDLK_EQUALS, SDLK_PLUS };
			case spic::input::KeyCode::OPENING_BRACKET_AND_OPENING_BRACE:
				return { SDLK_LEFTBRACKET, SDLK_KP_LEFTBRACE };
			case spic::input::KeyCode::CLOSING_BRACKET_AND_CLOSING_BRACE:
				return { SDLK_RIGHTBRACKET, SDLK_KP_RIGHTBRACE };
			case spic::input::KeyCode::BACKSLASH_AND_PIPE:
				return { SDLK_BACKSLASH, SDLK_KP_VERTICALBAR };
			case spic::input::KeyCode::NON_US_HASHMARK_AND_TILDE:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NONUSHASH) };
			case spic::input::KeyCode::SEMICOLON_AND_COLON:
				return { SDLK_SEMICOLON, SDLK_COLON };
			case spic::input::KeyCode::APOSTROPHE_AND_QUOTE:
				return { SDLK_QUOTE };
			case spic::input::KeyCode::GRAVE_ACCENT_AND_TILDE:
				return { SDLK_BACKQUOTE };
			case spic::input::KeyCode::COMMA_AND_LESS_THAN_SIGN:
				return { SDLK_COMMA, SDLK_LESS };
			case spic::input::KeyCode::DOT_AND_GREATER_THAN_SIGN:
				return { SDLK_PERIOD, SDLK_GREATER };
			case spic::input::KeyCode::SLASH_AND_QUESTION_MARK:
				return { SDLK_SLASH, SDLK_QUESTION };
			case spic::input::KeyCode::CAPS_LOCK:
				return { SDLK_CAPSLOCK };
			case spic::input::KeyCode::F1:
				return { SDLK_F1 };
			case spic::input::KeyCode::F2:
				return { SDLK_F2 };
			case spic::input::KeyCode::F3:
				return { SDLK_F3 };
			case spic::input::KeyCode::F4:
				return { SDLK_F4 };
			case spic::input::KeyCode::F5:
				return { SDLK_F5 };
			case spic::input::KeyCode::F6:
				return { SDLK_F6 };
			case spic::input::KeyCode::F7:
				return { SDLK_F7 };
			case spic::input::KeyCode::F8:
				return { SDLK_F8 };
			case spic::input::KeyCode::F9:
				return { SDLK_F9 };
			case spic::input::KeyCode::F10:
				return { SDLK_F10 };
			case spic::input::KeyCode::F11:
				return { SDLK_F11 };
			case spic::input::KeyCode::F12:
				return { SDLK_F12 };
			case spic::input::KeyCode::PRINT_SCREEN:
				return { SDLK_PRINTSCREEN };
			case spic::input::KeyCode::SCROLL_LOCK:
				return { SDLK_SCROLLLOCK };
			case spic::input::KeyCode::PAUSE:
				return { SDLK_PAUSE };
			case spic::input::KeyCode::INSERT:
				return { SDLK_INSERT };
			case spic::input::KeyCode::HOME:
				return { SDLK_HOME };
			case spic::input::KeyCode::PAGE_UP:
				return { SDLK_PAGEUP };
			case spic::input::KeyCode::DELETE:
				return { SDLK_DELETE };
			case spic::input::KeyCode::END:
				return { SDLK_END };
			case spic::input::KeyCode::PAGE_DOWN:
				return { SDLK_PAGEDOWN };
			case spic::input::KeyCode::RIGHT_ARROW:
				return { SDLK_RIGHT };
			case spic::input::KeyCode::LEFT_ARROW:
				return { SDLK_LEFT };
			case spic::input::KeyCode::DOWN_ARROW:
				return { SDLK_DOWN };
			case spic::input::KeyCode::UP_ARROW:
				return { SDLK_UP };
			case spic::input::KeyCode::NUM_LOCK:
				return { SDLK_NUMLOCKCLEAR };
			case spic::input::KeyCode::KEYPAD_SLASH:
				return { SDLK_KP_DIVIDE };
			case spic::input::KeyCode::KEYPAD_ASTERISK:
				return { SDLK_KP_MULTIPLY };
			case spic::input::KeyCode::KEYPAD_MINUS:
				return { SDLK_KP_MINUS };
			case spic::input::KeyCode::KEYPAD_PLUS:
				return { SDLK_KP_PLUS };
			case spic::input::KeyCode::KEYPAD_ENTER:
				return { SDLK_KP_ENTER };
			case spic::input::KeyCode::KEYPAD_1_AND_END:
				return { SDLK_KP_1 };
			case spic::input::KeyCode::KEYPAD_2_AND_DOWN_ARROW:
				return { SDLK_KP_2 };
			case spic::input::KeyCode::KEYPAD_3_AND_PAGE_DOWN:
				return { SDLK_KP_3 };
			case spic::input::KeyCode::KEYPAD_4_AND_LEFT_ARROW:
				return { SDLK_KP_4 };
			case spic::input::KeyCode::KEYPAD_5:
				return { SDLK_KP_5 };
			case spic::input::KeyCode::KEYPAD_6_AND_RIGHT_ARROW:
				return { SDLK_KP_6 };
			case spic::input::KeyCode::KEYPAD_7_AND_HOME:
				return { SDLK_KP_7 };
			case spic::input::KeyCode::KEYPAD_8_AND_UP_ARROW:
				return { SDLK_KP_8 };
			case spic::input::KeyCode::KEYPAD_9_AND_PAGE_UP:
				return { SDLK_KP_9 };
			case spic::input::KeyCode::KEYPAD_0_AND_INSERT:
				return { SDLK_KP_0 };
			case spic::input::KeyCode::KEYPAD_DOT_AND_DELETE:
				return { SDLK_KP_PERIOD };
			case spic::input::KeyCode::NON_US_BACKSLASH_AND_PIPE:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NONUSBACKSLASH) };
			case spic::input::KeyCode::APPLICATION:
				return { SDLK_APPLICATION };
			case spic::input::KeyCode::POWER:
				return { SDLK_POWER };
			case spic::input::KeyCode::KEYPAD_EQUAL_SIGN:
				return { SDLK_KP_EQUALS };
			case spic::input::KeyCode::F13:
				return { SDLK_F13 };
			case spic::input::KeyCode::F14:
				return { SDLK_F14 };
			case spic::input::KeyCode::F15:
				return { SDLK_F15 };
			case spic::input::KeyCode::F16:
				return { SDLK_F16 };
			case spic::input::KeyCode::F17:
				return { SDLK_F17 };
			case spic::input::KeyCode::F18:
				return { SDLK_F18 };
			case spic::input::KeyCode::F19:
				return { SDLK_F19 };
			case spic::input::KeyCode::F20:
				return { SDLK_F20 };
			case spic::input::KeyCode::F21:
				return { SDLK_F21 };
			case spic::input::KeyCode::F22:
				return { SDLK_F22 };
			case spic::input::KeyCode::F23:
				return { SDLK_F23 };
			case spic::input::KeyCode::F24:
				return { SDLK_F24 };
			case spic::input::KeyCode::EXECUTE:
				return { SDLK_EXECUTE };
			case spic::input::KeyCode::HELP:
				return { SDLK_HELP };
			case spic::input::KeyCode::MENU:
				return { SDLK_MENU };
			case spic::input::KeyCode::SELECT:
				return { SDLK_SELECT };
			case spic::input::KeyCode::STOP:
				return { SDLK_STOP };
			case spic::input::KeyCode::AGAIN:
				return { SDLK_AGAIN };
			case spic::input::KeyCode::UNDO:
				return { SDLK_UNDO };
			case spic::input::KeyCode::CUT:
				return { SDLK_CUT };
			case spic::input::KeyCode::COPY:
				return { SDLK_COPY };
			case spic::input::KeyCode::PASTE:
				return { SDLK_PASTE };
			case spic::input::KeyCode::FIND:
				return { SDLK_FIND };
			case spic::input::KeyCode::MUTE:
				return { SDLK_MUTE };
			case spic::input::KeyCode::VOLUME_UP:
				return { SDLK_VOLUMEUP };
			case spic::input::KeyCode::VOLUME_DOWN:
				return { SDLK_VOLUMEDOWN };
			case spic::input::KeyCode::LOCKING_CAPS_LOCK:
				return { SDLK_CAPSLOCK };
			case spic::input::KeyCode::LOCKING_NUM_LOCK:
				return { SDLK_NUMLOCKCLEAR };
			case spic::input::KeyCode::LOCKING_SCROLL_LOCK:
				return { SDLK_SCROLLLOCK };
			case spic::input::KeyCode::KEYPAD_COMMA:
				return { SDLK_KP_COMMA };
			case spic::input::KeyCode::KEYPAD_EQUAL_SIGN_AS400:
				return { SDLK_KP_EQUALSAS400 };
			case spic::input::KeyCode::INTERNATIONAL1:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL1) };
			case spic::input::KeyCode::INTERNATIONAL2:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL2) };
			case spic::input::KeyCode::INTERNATIONAL3:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL3) };
			case spic::input::KeyCode::INTERNATIONAL4:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL4) };
			case spic::input::KeyCode::INTERNATIONAL5:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL5) };
			case spic::input::KeyCode::INTERNATIONAL6:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL6) };
			case spic::input::KeyCode::INTERNATIONAL7:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL7) };
			case spic::input::KeyCode::INTERNATIONAL8:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL8) };
			case spic::input::KeyCode::INTERNATIONAL9:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL9) };
			case spic::input::KeyCode::LANG1:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG1) };
			case spic::input::KeyCode::LANG2:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG2) };
			case spic::input::KeyCode::LANG3:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG3) };
			case spic::input::KeyCode::LANG4:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG4) };
			case spic::input::KeyCode::LANG5:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG5) };
			case spic::input::KeyCode::LANG6:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG6) };
			case spic::input::KeyCode::LANG7:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG7) };
			case spic::input::KeyCode::LANG8:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG8) };
			case spic::input::KeyCode::LANG9:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG9) };
			case spic::input::KeyCode::ALTERNATE_ERASE:
				return { SDLK_ALTERASE };
			case spic::input::KeyCode::SYSREQ:
				return { SDLK_SYSREQ };
			case spic::input::KeyCode::CANCEL:
				return { SDLK_CANCEL };
			case spic::input::KeyCode::CLEAR:
				return { SDLK_CLEAR };
			case spic::input::KeyCode::PRIOR:
				return { SDLK_PRIOR };
			case spic::input::KeyCode::RETURN:
				return { SDLK_RETURN2 };
			case spic::input::KeyCode::SEPARATOR:
				return { SDLK_SEPARATOR };
			case spic::input::KeyCode::OUT:
				return { SDLK_OUT };
			case spic::input::KeyCode::OPER:
				return { SDLK_OPER };
			case spic::input::KeyCode::CLEAR_AND_AGAIN:
				return { SDLK_CLEARAGAIN };
			case spic::input::KeyCode::CRSEL_AND_PROPS:
				return { SDLK_CRSEL };
			case spic::input::KeyCode::EXSEL:
				return { SDLK_EXSEL };
			case spic::input::KeyCode::KEYPAD_00:
				return { SDLK_KP_00 };
			case spic::input::KeyCode::KEYPAD_000:
				return { SDLK_KP_000 };
			case spic::input::KeyCode::THOUSANDS_SEPARATOR:
				return { SDLK_THOUSANDSSEPARATOR };
			case spic::input::KeyCode::DECIMAL_SEPARATOR:
				return { SDLK_DECIMALSEPARATOR };
			case spic::input::KeyCode::CURRENCY_UNIT:
				return { SDLK_CURRENCYUNIT };
			case spic::input::KeyCode::CURRENCY_SUB_UNIT:
				return { SDLK_CURRENCYSUBUNIT };
			case spic::input::KeyCode::KEYPAD_OPENING_PARENTHESIS:
				return { SDLK_KP_LEFTPAREN };
			case spic::input::KeyCode::KEYPAD_CLOSING_PARENTHESIS:
				return { SDLK_KP_RIGHTPAREN };
			case spic::input::KeyCode::KEYPAD_OPENING_BRACE:
				return { SDLK_KP_LEFTBRACE };
			case spic::input::KeyCode::KEYPAD_CLOSING_BRACE:
				return { SDLK_KP_RIGHTBRACE };
			case spic::input::KeyCode::KEYPAD_TAB:
				return { SDLK_KP_TAB };
			case spic::input::KeyCode::KEYPAD_BACKSPACE:
				return { SDLK_KP_BACKSPACE };
			case spic::input::KeyCode::KEYPAD_A:
				return { SDLK_KP_A };
			case spic::input::KeyCode::KEYPAD_B:
				return { SDLK_KP_B };
			case spic::input::KeyCode::KEYPAD_C:
				return { SDLK_KP_C };
			case spic::input::KeyCode::KEYPAD_D:
				return { SDLK_KP_D };
			case spic::input::KeyCode::KEYPAD_E:
				return { SDLK_KP_E };
			case spic::input::KeyCode::KEYPAD_F:
				return { SDLK_KP_F };
			case spic::input::KeyCode::KEYPAD_XOR:
				return { SDLK_KP_XOR };
			case spic::input::KeyCode::KEYPAD_CARET:
				return { SDLK_KP_POWER };
			case spic::input::KeyCode::KEYPAD_PERCENTAGE:
				return { SDLK_KP_PERCENT };
			case spic::input::KeyCode::KEYPAD_LESS_THAN_SIGN:
				return { SDLK_KP_LESS };
			case spic::input::KeyCode::KEYPAD_GREATER_THAN_SIGN:
				return { SDLK_KP_GREATER };
			case spic::input::KeyCode::KEYPAD_AMP:
				return { SDLK_KP_AMPERSAND };
			case spic::input::KeyCode::KEYPAD_AMP_AMP:
				return { SDLK_KP_DBLAMPERSAND };
			case spic::input::KeyCode::KEYPAD_PIPE:
				return { SDLK_KP_VERTICALBAR };
			case spic::input::KeyCode::KEYPAD_PIPE_PIPE:
				return { SDLK_KP_DBLVERTICALBAR };
			case spic::input::KeyCode::KEYPAD_COLON:
				return { SDLK_KP_COLON };
			case spic::input::KeyCode::KEYPAD_HASHMARK:
				return { SDLK_KP_HASH };
			case spic::input::KeyCode::KEYPAD_SPACE:
				return { SDLK_KP_SPACE };
			case spic::input::KeyCode::KEYPAD_AT:
				return { SDLK_KP_AT };
			case spic::input::KeyCode::KEYPAD_EXCLAMATION_SIGN:
				return { SDLK_KP_EXCLAM };
			case spic::input::KeyCode::KEYPAD_MEMORY_STORE:
				return { SDLK_KP_MEMSTORE };
			case spic::input::KeyCode::KEYPAD_MEMORY_RECALL:
				return { SDLK_KP_MEMRECALL };
			case spic::input::KeyCode::KEYPAD_MEMORY_CLEAR:
				return { SDLK_KP_MEMCLEAR };
			case spic::input::KeyCode::KEYPAD_MEMORY_ADD:
				return { SDLK_KP_MEMADD };
			case spic::input::KeyCode::KEYPAD_MEMORY_SUBTRACT:
				return { SDLK_KP_MEMSUBTRACT };
			case spic::input::KeyCode::KEYPAD_MEMORY_MULTIPLY:
				return { SDLK_KP_MEMMULTIPLY };
			case spic::input::KeyCode::KEYPAD_MEMORY_DIVIDE:
				return { SDLK_KP_MEMDIVIDE };
			case spic::input::KeyCode::KEYPAD_PLUS_AND_MINUS:
				return { SDLK_KP_PLUSMINUS };
			case spic::input::KeyCode::KEYPAD_CLEAR:
				return { SDLK_KP_CLEAR };
			case spic::input::KeyCode::KEYPAD_CLEAR_ENTRY:
				return { SDLK_KP_CLEARENTRY };
			case spic::input::KeyCode::KEYPAD_BINARY:
				return { SDLK_KP_BINARY };
			case spic::input::KeyCode::KEYPAD_OCTAL:
				return { SDLK_KP_OCTAL };
			case spic::input::KeyCode::KEYPAD_DECIMAL:
				return { SDLK_KP_DECIMAL };
			case spic::input::KeyCode::KEYPAD_HEXADECIMAL:
				return { SDLK_KP_HEXADECIMAL };
			case spic::input::KeyCode::LEFT_CONTROL:
				return { SDLK_LCTRL };
			case spic::input::KeyCode::LEFT_SHIFT:
				return { SDLK_LSHIFT };
			case spic::input::KeyCode::LEFT_ALT:
				return { SDLK_LALT };
			case spic::input::KeyCode::LEFT_GUI:
				return { SDLK_LGUI };
			case spic::input::KeyCode::RIGHT_CONTROL:
				return { SDLK_RCTRL };
			case spic::input::KeyCode::RIGHT_SHIFT:
				return { SDLK_RSHIFT };
			case spic::input::KeyCode::RIGHT_ALT:
				return { SDLK_RALT };
			case spic::input::KeyCode::RIGHT_GUI:
				return { SDLK_RGUI };
			case spic::input::KeyCode::MEDIA_PLAY:
				return { SDLK_AUDIOPLAY };
			case spic::input::KeyCode::MEDIA_STOP:
				return { SDLK_AUDIOSTOP };
			case spic::input::KeyCode::MEDIA_PREVIOUS_TRACK:
				return { SDLK_AUDIOPREV };
			case spic::input::KeyCode::MEDIA_NEXT_TRACK:
				return { SDLK_AUDIONEXT };
			case spic::input::KeyCode::MEDIA_EJECT:
				return { SDLK_EJECT };
			case spic::input::KeyCode::MEDIA_VOLUME_UP:
				return { SDLK_KBDILLUMUP };
			case spic::input::KeyCode::MEDIA_VOLUME_DOWN:
				return { SDLK_KBDILLUMDOWN };
			case spic::input::KeyCode::MEDIA_MUTE:
				return { SDLK_AUDIOMUTE };
			case spic::input::KeyCode::MEDIA_WWW:
				return { SDLK_WWW };
			case spic::input::KeyCode::MEDIA_BACKWARD:
				return { SDLK_AC_BACK };
			case spic::input::KeyCode::MEDIA_FORWARD:
				return { SDLK_AC_FORWARD };
			case spic::input::KeyCode::MEDIA_CANCEL:
				return { SDLK_AC_STOP };
			case spic::input::KeyCode::MEDIA_SEARCH:
				return { SDLK_AC_SEARCH };
			case spic::input::KeyCode::MEDIA_SLEEP:
				return { SDLK_SLEEP };
			case spic::input::KeyCode::MEDIA_LOCK:
				return {};
			case spic::input::KeyCode::MEDIA_RELOAD:
				return { SDLK_AC_REFRESH };
			case spic::input::KeyCode::MEDIA_CALCULATOR:
				return { SDLK_CALCULATOR };
		}
		return { SDLK_UNKNOWN };
	}

	int Poll() 
	{
		return SDL_PollEvent(&ev);
	}

	bool Quit()
	{
		return ev.type == SDL_QUIT;
	}

	bool AnyKey() 
	{
		return ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP;
	}

	bool AnyKeyDown() 
	{
		return ev.type == SDL_KEYDOWN;
	}

	spic::Point MousePosition() 
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return spic::Point{ static_cast<float>(x),static_cast<float>(y) };
	}

	double GetAxis() 
	{
		return 2;
	}

	bool GetKey(spic::input::KeyCode key) 
	{
		const std::vector<SDL_Keycode> keyCodes = ToSDLKeyCodes(key);
		return std::find(keyCodes.begin(), keyCodes.end(), ev.key.keysym.sym) != keyCodes.end();
	}

	bool GetKeyDown(spic::input::KeyCode key) 
	{
		const std::vector<SDL_Keycode> keyCodes = ToSDLKeyCodes(key);
		return ev.type == SDL_KEYDOWN && std::find(keyCodes.begin(), keyCodes.end(), ev.key.keysym.sym) != keyCodes.end();
	}

	bool GetKeyUp(spic::input::KeyCode key) 
	{
		const std::vector<SDL_Keycode> keyCodes = ToSDLKeyCodes(key);
		return ev.type == SDL_KEYUP && std::find(keyCodes.begin(), keyCodes.end(), ev.key.keysym.sym) != keyCodes.end();
	}

	bool GetMouseButton(spic::input::MouseButton which) 
	{
		if (which == spic::input::MouseButton::LEFT)
			return ev.button.button == SDL_BUTTON_LEFT;

		if (which == spic::input::MouseButton::MIDDLE)
			return ev.button.button == SDL_BUTTON_MIDDLE;

		return ev.button.button == SDL_BUTTON_RIGHT;
	}

	bool GetMouseButtonDown(spic::input::MouseButton which) 
	{
		if (ev.type != SDL_MOUSEBUTTONDOWN)
			return false;

		if (which == spic::input::MouseButton::LEFT)
			return ev.button.button == SDL_BUTTON_LEFT;

		if (which == spic::input::MouseButton::MIDDLE)
			return ev.button.button == SDL_BUTTON_MIDDLE;

		return ev.button.button == SDL_BUTTON_RIGHT;
	}

	bool GetMouseButtonUp(spic::input::MouseButton which) 
	{
		if (ev.type != SDL_MOUSEBUTTONUP)
			return false;

		if (which == spic::input::MouseButton::LEFT)
			return ev.button.button == SDL_BUTTON_LEFT;

		if (which == spic::input::MouseButton::MIDDLE)
			return ev.button.button == SDL_BUTTON_MIDDLE;

		return ev.button.button == SDL_BUTTON_RIGHT;
	}
}