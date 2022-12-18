#include "InputImpl.hpp"
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include <SDL2/SDL_events.h>
#pragma warning( pop )

namespace spic::internal::InputImpl {
	SDL_Event ev;

	std::vector<SDL_Keycode> ToSDLKeyCodes(spic::Input::KeyCode key) 
	{
		switch (key) 
		{
			case spic::Input::KeyCode::ERROR_ROLLOVER:
				return {};
			case spic::Input::KeyCode::POST_FAIL:
				return {};
			case spic::Input::KeyCode::ERROR_UNDEFINED:
				return {};
			case spic::Input::KeyCode::A:
				return { SDLK_a };
			case spic::Input::KeyCode::B:
				return { SDLK_b };
			case spic::Input::KeyCode::C:
				return { SDLK_c };
			case spic::Input::KeyCode::D:
				return { SDLK_d };
			case spic::Input::KeyCode::E:
				return { SDLK_e };
			case spic::Input::KeyCode::F:
				return { SDLK_f };
			case spic::Input::KeyCode::G:
				return { SDLK_g };
			case spic::Input::KeyCode::H:
				return { SDLK_h };
			case spic::Input::KeyCode::I:
				return { SDLK_i };
			case spic::Input::KeyCode::J:
				return { SDLK_j };
			case spic::Input::KeyCode::K:
				return { SDLK_k };
			case spic::Input::KeyCode::L:
				return { SDLK_l };
			case spic::Input::KeyCode::M:
				return { SDLK_m };
			case spic::Input::KeyCode::N:
				return { SDLK_n };
			case spic::Input::KeyCode::O:
				return { SDLK_o };
			case spic::Input::KeyCode::P:
				return { SDLK_p };
			case spic::Input::KeyCode::Q:
				return { SDLK_q };
			case spic::Input::KeyCode::R:
				return { SDLK_r };
			case spic::Input::KeyCode::S:
				return { SDLK_s };
			case spic::Input::KeyCode::T:
				return { SDLK_t };
			case spic::Input::KeyCode::U:
				return { SDLK_u };
			case spic::Input::KeyCode::V:
				return { SDLK_v };
			case spic::Input::KeyCode::W:
				return { SDLK_w };
			case spic::Input::KeyCode::X:
				return { SDLK_x };
			case spic::Input::KeyCode::Y:
				return { SDLK_y };
			case spic::Input::KeyCode::Z:
				return { SDLK_z };
			case spic::Input::KeyCode::NUMBER_1_AND_EXCLAMATION:
				return { SDLK_1, SDLK_EXCLAIM };
			case spic::Input::KeyCode::NUMBER_2_AND_AT:
				return { SDLK_2, SDLK_AT };
			case spic::Input::KeyCode::NUMBER_3_AND_HASHMARK:
				return { SDLK_3, SDLK_HASH };
			case spic::Input::KeyCode::NUMBER_4_AND_DOLLAR:
				return { SDLK_4, SDLK_DOLLAR };
			case spic::Input::KeyCode::NUMBER_5_AND_PERCENTAGE:
				return { SDLK_5, SDLK_PERCENT };
			case spic::Input::KeyCode::NUMBER_6_AND_CARET:
				return { SDLK_6, SDLK_CARET };
			case spic::Input::KeyCode::NUMBER_7_AND_AMPERSAND:
				return { SDLK_7, SDLK_AMPERSAND };
			case spic::Input::KeyCode::NUMBER_8_AND_ASTERISK:
				return { SDLK_8, SDLK_ASTERISK };
			case spic::Input::KeyCode::NUMBER_9_AND_OPENING_PARENTHESIS:
				return { SDLK_9, SDLK_LEFTPAREN };
			case spic::Input::KeyCode::NUMBER_0_AND_CLOSING_PARENTHESIS:
				return { SDLK_0, SDLK_RIGHTPAREN };
			case spic::Input::KeyCode::ENTER:
				return { SDLK_KP_ENTER };
			case spic::Input::KeyCode::ESCAPE:
				return { SDLK_ESCAPE };
			case spic::Input::KeyCode::BACKSPACE:
				return { SDLK_BACKSPACE };
			case spic::Input::KeyCode::TAB:
				return { SDLK_TAB };
			case spic::Input::KeyCode::SPACE:
				return { SDLK_SPACE };
			case spic::Input::KeyCode::MINUS_AND_UNDERSCORE:
				return { SDLK_MINUS, SDLK_UNDERSCORE };
			case spic::Input::KeyCode::EQUAL_AND_PLUS:
				return { SDLK_EQUALS, SDLK_PLUS };
			case spic::Input::KeyCode::OPENING_BRACKET_AND_OPENING_BRACE:
				return { SDLK_LEFTBRACKET, SDLK_KP_LEFTBRACE };
			case spic::Input::KeyCode::CLOSING_BRACKET_AND_CLOSING_BRACE:
				return { SDLK_RIGHTBRACKET, SDLK_KP_RIGHTBRACE };
			case spic::Input::KeyCode::BACKSLASH_AND_PIPE:
				return { SDLK_BACKSLASH, SDLK_KP_VERTICALBAR };
			case spic::Input::KeyCode::NON_US_HASHMARK_AND_TILDE:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NONUSHASH) };
			case spic::Input::KeyCode::SEMICOLON_AND_COLON:
				return { SDLK_SEMICOLON, SDLK_COLON };
			case spic::Input::KeyCode::APOSTROPHE_AND_QUOTE:
				return { SDLK_QUOTE };
			case spic::Input::KeyCode::GRAVE_ACCENT_AND_TILDE:
				return { SDLK_BACKQUOTE };
			case spic::Input::KeyCode::COMMA_AND_LESS_THAN_SIGN:
				return { SDLK_COMMA, SDLK_LESS };
			case spic::Input::KeyCode::DOT_AND_GREATER_THAN_SIGN:
				return { SDLK_PERIOD, SDLK_GREATER };
			case spic::Input::KeyCode::SLASH_AND_QUESTION_MARK:
				return { SDLK_SLASH, SDLK_QUESTION };
			case spic::Input::KeyCode::CAPS_LOCK:
				return { SDLK_CAPSLOCK };
			case spic::Input::KeyCode::F1:
				return { SDLK_F1 };
			case spic::Input::KeyCode::F2:
				return { SDLK_F2 };
			case spic::Input::KeyCode::F3:
				return { SDLK_F3 };
			case spic::Input::KeyCode::F4:
				return { SDLK_F4 };
			case spic::Input::KeyCode::F5:
				return { SDLK_F5 };
			case spic::Input::KeyCode::F6:
				return { SDLK_F6 };
			case spic::Input::KeyCode::F7:
				return { SDLK_F7 };
			case spic::Input::KeyCode::F8:
				return { SDLK_F8 };
			case spic::Input::KeyCode::F9:
				return { SDLK_F9 };
			case spic::Input::KeyCode::F10:
				return { SDLK_F10 };
			case spic::Input::KeyCode::F11:
				return { SDLK_F11 };
			case spic::Input::KeyCode::F12:
				return { SDLK_F12 };
			case spic::Input::KeyCode::PRINT_SCREEN:
				return { SDLK_PRINTSCREEN };
			case spic::Input::KeyCode::SCROLL_LOCK:
				return { SDLK_SCROLLLOCK };
			case spic::Input::KeyCode::PAUSE:
				return { SDLK_PAUSE };
			case spic::Input::KeyCode::INSERT:
				return { SDLK_INSERT };
			case spic::Input::KeyCode::HOME:
				return { SDLK_HOME };
			case spic::Input::KeyCode::PAGE_UP:
				return { SDLK_PAGEUP };
			case spic::Input::KeyCode::DELETE:
				return { SDLK_DELETE };
			case spic::Input::KeyCode::END:
				return { SDLK_END };
			case spic::Input::KeyCode::PAGE_DOWN:
				return { SDLK_PAGEDOWN };
			case spic::Input::KeyCode::RIGHT_ARROW:
				return { SDLK_RIGHT };
			case spic::Input::KeyCode::LEFT_ARROW:
				return { SDLK_LEFT };
			case spic::Input::KeyCode::DOWN_ARROW:
				return { SDLK_DOWN };
			case spic::Input::KeyCode::UP_ARROW:
				return { SDLK_UP };
			case spic::Input::KeyCode::NUM_LOCK:
				return { SDLK_NUMLOCKCLEAR };
			case spic::Input::KeyCode::KEYPAD_SLASH:
				return { SDLK_KP_DIVIDE };
			case spic::Input::KeyCode::KEYPAD_ASTERISK:
				return { SDLK_KP_MULTIPLY };
			case spic::Input::KeyCode::KEYPAD_MINUS:
				return { SDLK_KP_MINUS };
			case spic::Input::KeyCode::KEYPAD_PLUS:
				return { SDLK_KP_PLUS };
			case spic::Input::KeyCode::KEYPAD_ENTER:
				return { SDLK_KP_ENTER };
			case spic::Input::KeyCode::KEYPAD_1_AND_END:
				return { SDLK_KP_1 };
			case spic::Input::KeyCode::KEYPAD_2_AND_DOWN_ARROW:
				return { SDLK_KP_2 };
			case spic::Input::KeyCode::KEYPAD_3_AND_PAGE_DOWN:
				return { SDLK_KP_3 };
			case spic::Input::KeyCode::KEYPAD_4_AND_LEFT_ARROW:
				return { SDLK_KP_4 };
			case spic::Input::KeyCode::KEYPAD_5:
				return { SDLK_KP_5 };
			case spic::Input::KeyCode::KEYPAD_6_AND_RIGHT_ARROW:
				return { SDLK_KP_6 };
			case spic::Input::KeyCode::KEYPAD_7_AND_HOME:
				return { SDLK_KP_7 };
			case spic::Input::KeyCode::KEYPAD_8_AND_UP_ARROW:
				return { SDLK_KP_8 };
			case spic::Input::KeyCode::KEYPAD_9_AND_PAGE_UP:
				return { SDLK_KP_9 };
			case spic::Input::KeyCode::KEYPAD_0_AND_INSERT:
				return { SDLK_KP_0 };
			case spic::Input::KeyCode::KEYPAD_DOT_AND_DELETE:
				return { SDLK_KP_PERIOD };
			case spic::Input::KeyCode::NON_US_BACKSLASH_AND_PIPE:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NONUSBACKSLASH) };
			case spic::Input::KeyCode::APPLICATION:
				return { SDLK_APPLICATION };
			case spic::Input::KeyCode::POWER:
				return { SDLK_POWER };
			case spic::Input::KeyCode::KEYPAD_EQUAL_SIGN:
				return { SDLK_KP_EQUALS };
			case spic::Input::KeyCode::F13:
				return { SDLK_F13 };
			case spic::Input::KeyCode::F14:
				return { SDLK_F14 };
			case spic::Input::KeyCode::F15:
				return { SDLK_F15 };
			case spic::Input::KeyCode::F16:
				return { SDLK_F16 };
			case spic::Input::KeyCode::F17:
				return { SDLK_F17 };
			case spic::Input::KeyCode::F18:
				return { SDLK_F18 };
			case spic::Input::KeyCode::F19:
				return { SDLK_F19 };
			case spic::Input::KeyCode::F20:
				return { SDLK_F20 };
			case spic::Input::KeyCode::F21:
				return { SDLK_F21 };
			case spic::Input::KeyCode::F22:
				return { SDLK_F22 };
			case spic::Input::KeyCode::F23:
				return { SDLK_F23 };
			case spic::Input::KeyCode::F24:
				return { SDLK_F24 };
			case spic::Input::KeyCode::EXECUTE:
				return { SDLK_EXECUTE };
			case spic::Input::KeyCode::HELP:
				return { SDLK_HELP };
			case spic::Input::KeyCode::MENU:
				return { SDLK_MENU };
			case spic::Input::KeyCode::SELECT:
				return { SDLK_SELECT };
			case spic::Input::KeyCode::STOP:
				return { SDLK_STOP };
			case spic::Input::KeyCode::AGAIN:
				return { SDLK_AGAIN };
			case spic::Input::KeyCode::UNDO:
				return { SDLK_UNDO };
			case spic::Input::KeyCode::CUT:
				return { SDLK_CUT };
			case spic::Input::KeyCode::COPY:
				return { SDLK_COPY };
			case spic::Input::KeyCode::PASTE:
				return { SDLK_PASTE };
			case spic::Input::KeyCode::FIND:
				return { SDLK_FIND };
			case spic::Input::KeyCode::MUTE:
				return { SDLK_MUTE };
			case spic::Input::KeyCode::VOLUME_UP:
				return { SDLK_VOLUMEUP };
			case spic::Input::KeyCode::VOLUME_DOWN:
				return { SDLK_VOLUMEDOWN };
			case spic::Input::KeyCode::LOCKING_CAPS_LOCK:
				return { SDLK_CAPSLOCK };
			case spic::Input::KeyCode::LOCKING_NUM_LOCK:
				return { SDLK_NUMLOCKCLEAR };
			case spic::Input::KeyCode::LOCKING_SCROLL_LOCK:
				return { SDLK_SCROLLLOCK };
			case spic::Input::KeyCode::KEYPAD_COMMA:
				return { SDLK_KP_COMMA };
			case spic::Input::KeyCode::KEYPAD_EQUAL_SIGN_AS400:
				return { SDLK_KP_EQUALSAS400 };
			case spic::Input::KeyCode::INTERNATIONAL1:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL1) };
			case spic::Input::KeyCode::INTERNATIONAL2:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL2) };
			case spic::Input::KeyCode::INTERNATIONAL3:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL3) };
			case spic::Input::KeyCode::INTERNATIONAL4:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL4) };
			case spic::Input::KeyCode::INTERNATIONAL5:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL5) };
			case spic::Input::KeyCode::INTERNATIONAL6:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL6) };
			case spic::Input::KeyCode::INTERNATIONAL7:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL7) };
			case spic::Input::KeyCode::INTERNATIONAL8:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL8) };
			case spic::Input::KeyCode::INTERNATIONAL9:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INTERNATIONAL9) };
			case spic::Input::KeyCode::LANG1:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG1) };
			case spic::Input::KeyCode::LANG2:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG2) };
			case spic::Input::KeyCode::LANG3:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG3) };
			case spic::Input::KeyCode::LANG4:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG4) };
			case spic::Input::KeyCode::LANG5:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG5) };
			case spic::Input::KeyCode::LANG6:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG6) };
			case spic::Input::KeyCode::LANG7:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG7) };
			case spic::Input::KeyCode::LANG8:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG8) };
			case spic::Input::KeyCode::LANG9:
				return { SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LANG9) };
			case spic::Input::KeyCode::ALTERNATE_ERASE:
				return { SDLK_ALTERASE };
			case spic::Input::KeyCode::SYSREQ:
				return { SDLK_SYSREQ };
			case spic::Input::KeyCode::CANCEL:
				return { SDLK_CANCEL };
			case spic::Input::KeyCode::CLEAR:
				return { SDLK_CLEAR };
			case spic::Input::KeyCode::PRIOR:
				return { SDLK_PRIOR };
			case spic::Input::KeyCode::RETURN:
				return { SDLK_RETURN2 };
			case spic::Input::KeyCode::SEPARATOR:
				return { SDLK_SEPARATOR };
			case spic::Input::KeyCode::OUT:
				return { SDLK_OUT };
			case spic::Input::KeyCode::OPER:
				return { SDLK_OPER };
			case spic::Input::KeyCode::CLEAR_AND_AGAIN:
				return { SDLK_CLEARAGAIN };
			case spic::Input::KeyCode::CRSEL_AND_PROPS:
				return { SDLK_CRSEL };
			case spic::Input::KeyCode::EXSEL:
				return { SDLK_EXSEL };
			case spic::Input::KeyCode::KEYPAD_00:
				return { SDLK_KP_00 };
			case spic::Input::KeyCode::KEYPAD_000:
				return { SDLK_KP_000 };
			case spic::Input::KeyCode::THOUSANDS_SEPARATOR:
				return { SDLK_THOUSANDSSEPARATOR };
			case spic::Input::KeyCode::DECIMAL_SEPARATOR:
				return { SDLK_DECIMALSEPARATOR };
			case spic::Input::KeyCode::CURRENCY_UNIT:
				return { SDLK_CURRENCYUNIT };
			case spic::Input::KeyCode::CURRENCY_SUB_UNIT:
				return { SDLK_CURRENCYSUBUNIT };
			case spic::Input::KeyCode::KEYPAD_OPENING_PARENTHESIS:
				return { SDLK_KP_LEFTPAREN };
			case spic::Input::KeyCode::KEYPAD_CLOSING_PARENTHESIS:
				return { SDLK_KP_RIGHTPAREN };
			case spic::Input::KeyCode::KEYPAD_OPENING_BRACE:
				return { SDLK_KP_LEFTBRACE };
			case spic::Input::KeyCode::KEYPAD_CLOSING_BRACE:
				return { SDLK_KP_RIGHTBRACE };
			case spic::Input::KeyCode::KEYPAD_TAB:
				return { SDLK_KP_TAB };
			case spic::Input::KeyCode::KEYPAD_BACKSPACE:
				return { SDLK_KP_BACKSPACE };
			case spic::Input::KeyCode::KEYPAD_A:
				return { SDLK_KP_A };
			case spic::Input::KeyCode::KEYPAD_B:
				return { SDLK_KP_B };
			case spic::Input::KeyCode::KEYPAD_C:
				return { SDLK_KP_C };
			case spic::Input::KeyCode::KEYPAD_D:
				return { SDLK_KP_D };
			case spic::Input::KeyCode::KEYPAD_E:
				return { SDLK_KP_E };
			case spic::Input::KeyCode::KEYPAD_F:
				return { SDLK_KP_F };
			case spic::Input::KeyCode::KEYPAD_XOR:
				return { SDLK_KP_XOR };
			case spic::Input::KeyCode::KEYPAD_CARET:
				return { SDLK_KP_POWER };
			case spic::Input::KeyCode::KEYPAD_PERCENTAGE:
				return { SDLK_KP_PERCENT };
			case spic::Input::KeyCode::KEYPAD_LESS_THAN_SIGN:
				return { SDLK_KP_LESS };
			case spic::Input::KeyCode::KEYPAD_GREATER_THAN_SIGN:
				return { SDLK_KP_GREATER };
			case spic::Input::KeyCode::KEYPAD_AMP:
				return { SDLK_KP_AMPERSAND };
			case spic::Input::KeyCode::KEYPAD_AMP_AMP:
				return { SDLK_KP_DBLAMPERSAND };
			case spic::Input::KeyCode::KEYPAD_PIPE:
				return { SDLK_KP_VERTICALBAR };
			case spic::Input::KeyCode::KEYPAD_PIPE_PIPE:
				return { SDLK_KP_DBLVERTICALBAR };
			case spic::Input::KeyCode::KEYPAD_COLON:
				return { SDLK_KP_COLON };
			case spic::Input::KeyCode::KEYPAD_HASHMARK:
				return { SDLK_KP_HASH };
			case spic::Input::KeyCode::KEYPAD_SPACE:
				return { SDLK_KP_SPACE };
			case spic::Input::KeyCode::KEYPAD_AT:
				return { SDLK_KP_AT };
			case spic::Input::KeyCode::KEYPAD_EXCLAMATION_SIGN:
				return { SDLK_KP_EXCLAM };
			case spic::Input::KeyCode::KEYPAD_MEMORY_STORE:
				return { SDLK_KP_MEMSTORE };
			case spic::Input::KeyCode::KEYPAD_MEMORY_RECALL:
				return { SDLK_KP_MEMRECALL };
			case spic::Input::KeyCode::KEYPAD_MEMORY_CLEAR:
				return { SDLK_KP_MEMCLEAR };
			case spic::Input::KeyCode::KEYPAD_MEMORY_ADD:
				return { SDLK_KP_MEMADD };
			case spic::Input::KeyCode::KEYPAD_MEMORY_SUBTRACT:
				return { SDLK_KP_MEMSUBTRACT };
			case spic::Input::KeyCode::KEYPAD_MEMORY_MULTIPLY:
				return { SDLK_KP_MEMMULTIPLY };
			case spic::Input::KeyCode::KEYPAD_MEMORY_DIVIDE:
				return { SDLK_KP_MEMDIVIDE };
			case spic::Input::KeyCode::KEYPAD_PLUS_AND_MINUS:
				return { SDLK_KP_PLUSMINUS };
			case spic::Input::KeyCode::KEYPAD_CLEAR:
				return { SDLK_KP_CLEAR };
			case spic::Input::KeyCode::KEYPAD_CLEAR_ENTRY:
				return { SDLK_KP_CLEARENTRY };
			case spic::Input::KeyCode::KEYPAD_BINARY:
				return { SDLK_KP_BINARY };
			case spic::Input::KeyCode::KEYPAD_OCTAL:
				return { SDLK_KP_OCTAL };
			case spic::Input::KeyCode::KEYPAD_DECIMAL:
				return { SDLK_KP_DECIMAL };
			case spic::Input::KeyCode::KEYPAD_HEXADECIMAL:
				return { SDLK_KP_HEXADECIMAL };
			case spic::Input::KeyCode::LEFT_CONTROL:
				return { SDLK_LCTRL };
			case spic::Input::KeyCode::LEFT_SHIFT:
				return { SDLK_LSHIFT };
			case spic::Input::KeyCode::LEFT_ALT:
				return { SDLK_LALT };
			case spic::Input::KeyCode::LEFT_GUI:
				return { SDLK_LGUI };
			case spic::Input::KeyCode::RIGHT_CONTROL:
				return { SDLK_RCTRL };
			case spic::Input::KeyCode::RIGHT_SHIFT:
				return { SDLK_RSHIFT };
			case spic::Input::KeyCode::RIGHT_ALT:
				return { SDLK_RALT };
			case spic::Input::KeyCode::RIGHT_GUI:
				return { SDLK_RGUI };
			case spic::Input::KeyCode::MEDIA_PLAY:
				return { SDLK_AUDIOPLAY };
			case spic::Input::KeyCode::MEDIA_STOP:
				return { SDLK_AUDIOSTOP };
			case spic::Input::KeyCode::MEDIA_PREVIOUS_TRACK:
				return { SDLK_AUDIOPREV };
			case spic::Input::KeyCode::MEDIA_NEXT_TRACK:
				return { SDLK_AUDIONEXT };
			case spic::Input::KeyCode::MEDIA_EJECT:
				return { SDLK_EJECT };
			case spic::Input::KeyCode::MEDIA_VOLUME_UP:
				return { SDLK_KBDILLUMUP };
			case spic::Input::KeyCode::MEDIA_VOLUME_DOWN:
				return { SDLK_KBDILLUMDOWN };
			case spic::Input::KeyCode::MEDIA_MUTE:
				return { SDLK_AUDIOMUTE };
			case spic::Input::KeyCode::MEDIA_WWW:
				return { SDLK_WWW };
			case spic::Input::KeyCode::MEDIA_BACKWARD:
				return { SDLK_AC_BACK };
			case spic::Input::KeyCode::MEDIA_FORWARD:
				return { SDLK_AC_FORWARD };
			case spic::Input::KeyCode::MEDIA_CANCEL:
				return { SDLK_AC_STOP };
			case spic::Input::KeyCode::MEDIA_SEARCH:
				return { SDLK_AC_SEARCH };
			case spic::Input::KeyCode::MEDIA_SLEEP:
				return { SDLK_SLEEP };
			case spic::Input::KeyCode::MEDIA_LOCK:
				return {};
			case spic::Input::KeyCode::MEDIA_RELOAD:
				return { SDLK_AC_REFRESH };
			case spic::Input::KeyCode::MEDIA_CALCULATOR:
				return { SDLK_CALCULATOR };
		}
		return { SDLK_UNKNOWN };
	}

	int InputImpl::Poll() 
	{
		return SDL_PollEvent(&ev);
	}

	bool InputImpl::Quit()
	{
		return ev.type == SDL_QUIT;
	}

	bool InputImpl::AnyKey() 
	{
		return ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP;
	}

	bool InputImpl::AnyKeyDown() 
	{
		return ev.type == SDL_KEYDOWN;
	}

	spic::Point InputImpl::MousePosition() 
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return spic::Point{ static_cast<float>(x),static_cast<float>(y) };
	}

	double InputImpl::GetAxis() 
	{
		return 2;
	}

	bool InputImpl::GetKey(spic::Input::KeyCode key) 
	{
		const std::vector<SDL_Keycode> keyCodes = ToSDLKeyCodes(key);
		return std::find(keyCodes.begin(), keyCodes.end(), ev.key.keysym.sym) != keyCodes.end();
	}

	bool InputImpl::GetKeyDown(spic::Input::KeyCode key) 
	{
		const std::vector<SDL_Keycode> keyCodes = ToSDLKeyCodes(key);
		return ev.type == SDL_KEYDOWN && std::find(keyCodes.begin(), keyCodes.end(), ev.key.keysym.sym) != keyCodes.end();
	}

	bool InputImpl::GetKeyUp(spic::Input::KeyCode key) 
	{
		const std::vector<SDL_Keycode> keyCodes = ToSDLKeyCodes(key);
		return ev.type == SDL_KEYUP && std::find(keyCodes.begin(), keyCodes.end(), ev.key.keysym.sym) != keyCodes.end();
	}

	bool InputImpl::GetMouseButton(spic::Input::MouseButton which) 
	{
		if (which == spic::Input::MouseButton::LEFT)
			return ev.button.button == SDL_BUTTON_LEFT;

		if (which == spic::Input::MouseButton::MIDDLE)
			return ev.button.button == SDL_BUTTON_MIDDLE;

		return ev.button.button == SDL_BUTTON_RIGHT;
	}

	bool InputImpl::GetMouseButtonDown(spic::Input::MouseButton which) 
	{
		if (ev.type != SDL_MOUSEBUTTONDOWN)
			return false;

		if (which == spic::Input::MouseButton::LEFT)
			return ev.button.button == SDL_BUTTON_LEFT;

		if (which == spic::Input::MouseButton::MIDDLE)
			return ev.button.button == SDL_BUTTON_MIDDLE;

		return ev.button.button == SDL_BUTTON_RIGHT;
	}

	bool InputImpl::GetMouseButtonUp(spic::Input::MouseButton which) 
	{
		if (ev.type != SDL_MOUSEBUTTONUP)
			return false;

		if (which == spic::Input::MouseButton::LEFT)
			return ev.button.button == SDL_BUTTON_LEFT;

		if (which == spic::Input::MouseButton::MIDDLE)
			return ev.button.button == SDL_BUTTON_MIDDLE;

		return ev.button.button == SDL_BUTTON_RIGHT;
	}
}