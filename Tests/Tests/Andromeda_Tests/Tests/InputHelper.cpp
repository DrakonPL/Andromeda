#include "InputHelper.h"
#include <Andromeda/Utils/Logger.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <Andromeda/Graphics/RenderManager.h>

using namespace Andromeda;
using namespace Andromeda::Graphics;

InputHelper* InputHelper::_inputHelper = 0;

void InputHelper::PrepareKeyboardMapping()
{
	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::Down, Key::Code::Down));
	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::Up, Key::Code::Up));
	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::Left, Key::Code::Left));
	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::Right, Key::Code::Right));

	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::RotateLeft, Key::Code::Q));
	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::RotateRight, Key::Code::E));

	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::Next, Key::Code::Space));
	_keyboardMapping.insert(std::pair<InputAction, Key::Code>(InputAction::Exit, Key::Code::Escape));

	for (int key = 0; key < Key::Code::Count; key++)
	{
		Key::Code code = static_cast<Key::Code>(key);
		_keyPresseddMapping.insert(std::pair<Key::Code, bool>(code, false));
	}
}

void InputHelper::PrepareGamepadMapping()
{
	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::Down, Gamepad::Button::Down));
	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::Up, Gamepad::Button::Up));
	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::Left, Gamepad::Button::Left));
	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::Right, Gamepad::Button::Right));

	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::RotateLeft, Gamepad::Button::LTrigger));
	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::RotateRight, Gamepad::Button::RTrigger));

	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::Next, Gamepad::Button::Start));
	_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(InputAction::Exit, Gamepad::Button::Select));

	for (int key = 0; key < Gamepad::Button::Count; key++)
	{
		Gamepad::Button button = static_cast<Gamepad::Button>(key);
		_buttonPressed.insert(std::pair<Gamepad::Button, bool>(button, false));
	}
}

void InputHelper::PrepareNameKeyboardMapping()
{
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::W, "W"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::D, "D"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::S, "S"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::A, "A"));

	//left,right...
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::Left, "Left"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::Right, "Right"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::Up, "Up"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::Down, "Down"));

	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::Q, "Q"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::E, "E"));

	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::Space, "Space"));
	_nameKeyboardMapping.insert(std::pair<Key::Code, std::string>(Key::Code::Return, "Return"));

}

void InputHelper::PrepareNameGamepadMapping()
{
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Up, "Up"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Down, "Down"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Left, "Left"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Right, "Right"));

	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Triangle, "Triangle"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Square, "Square"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Circle, "Circle"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Cross, "Cross"));

	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Start, "Start"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::Select, "Select"));

	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::LTrigger, "LTrigger"));
	_nameGamepadMapping.insert(std::pair<Gamepad::Button, std::string>(Gamepad::Button::RTrigger, "RTrigger"));
}

InputHelper::InputHelper()
{
	_inputManager = InputManager::Instance();

	if (_inputManager->GetKayboardCount() > 0)
	{
		_keyboard = _inputManager->GetKeyboardDevice(0);
		_mode = InputActionMode::PC;
	}
	else
	{
		_gamepad = _inputManager->GetGamepadDevice(0);
		_mode = InputActionMode::VITA;
	}

	for (size_t i = 0; i < InputAction::Count; i++)
	{
		_actionPressed.insert(std::pair<InputAction, bool>(static_cast<InputAction>(i), false));
	}

	if (_mode == InputActionMode::PC)
	{
		PrepareKeyboardMapping();
		PrepareNameKeyboardMapping();
	}
	else
	{
		PrepareGamepadMapping();
		PrepareNameGamepadMapping();
	}	

	//touch devices
	if (_mode == InputActionMode::PC)
	{
		_mouseDevice = _inputManager->GetMouseDevice(0);
	}else
	{
		_touchDevice = _inputManager->GetTouchDevice(0);
	}

	_updateAll = false;
}

InputHelper* InputHelper::Instance()
{
	if (_inputHelper == 0)
	{
		_inputHelper = new InputHelper();
	}

	return _inputHelper;
}

InputHelper::~InputHelper()
{
	_actionPressed.clear();
	_keyboardMapping.clear();
	_gamepadMapping.clear();
}

bool InputHelper::ActionPressed(InputAction action)
{
	if (_mode == InputActionMode::PC)
	{
		if (_keyboard->KeyDown(_keyboardMapping[action]) && !_actionPressed[action])
		{
			_actionPressed[action] = true;
			return true;
		}
	}
	else
	{
		if (_gamepad->KeyDown(_gamepadMapping[action]) && !_actionPressed[action])
		{
			_actionPressed[action] = true;
			return true;
		}
	}

	return false;
}

bool InputHelper::ActionHold(InputAction action)
{
	if (_mode == InputActionMode::PC)
	{
		if (_keyboard->KeyDown(_keyboardMapping[action]))
		{
			return true;
		}
	}
	else
	{
		if (_gamepad->KeyDown(_gamepadMapping[action]))
		{
			return true;
		}
	}

	return false;
}

int InputHelper::GetTouchCount()
{
	if (_mode == InputActionMode::PC)
	{
		if (_mouseDevice->ButtonDown(Mouse::Button::Left))
		{
			return 1;
		}

		return 0;
	}else
	{
		return _touchDevice->GetTouchCount();
	}
}

glm::vec2 InputHelper::GetTouchPosition(int touch)
{
	if (_mode == InputActionMode::PC)
	{
		int x = _mouseDevice->GetPosX();
		int y = _mouseDevice->GetPosY();

		return glm::vec2(x, y);
	}
	else
	{
		float x = ((float)_touchDevice->GetTouchX(touch) / 1920.0f) * RenderManager::Instance()->GetWidth();
		float y = ((float)_touchDevice->GetTouchY(touch) / 1088.0f) * RenderManager::Instance()->GetHeight();

		return glm::vec2(x, y);
	}
}

void InputHelper::UpdateAllInputs(bool state)
{
	_updateAll = true;
}

void InputHelper::Update()
{
	for (size_t i = 0; i < InputAction::Count; i++)
	{
		InputAction action = static_cast<InputAction>(i);
		if (_mode == InputActionMode::PC)
		{
			// check action
			if (_keyboard->KeyUp(_keyboardMapping[action]))
			{
				_actionPressed[action] = false;
			}else
			{
				_actionPressed[action] = true;
			}				
		}
		else
		{
			if (_gamepad->KeyUp(_gamepadMapping[action]))
			{
				_actionPressed[action] = false;
			}else
			{
				_actionPressed[action] = true;
			}			
		}
	}

	if (_updateAll)
	{
		if (_mode == InputActionMode::PC)
		{
			//check all keys
			for (int key = 0; key < Key::Code::Count; key++)
			{
				Key::Code code = static_cast<Key::Code>(key);
				if (_keyboard->KeyUp(code))
				{
					_keyPresseddMapping[code] = false;
				}
				else
				{
					_keyPresseddMapping[code] = true;
				}
			}
		}
		else
		{
			for (int key = 0; key < Gamepad::Button::Count; key++)
			{
				Gamepad::Button button = static_cast<Gamepad::Button>(key);
				if (_gamepad->KeyUp(button))
				{
					_buttonPressed[button] = false;
				}
				else
				{
					_buttonPressed[button] = true;
				}
			}
		}		
	}
}

bool InputHelper::ChangeInputForAction(InputAction action)
{
	if (_mode == InputActionMode::PC)
	{
		for (int key = 0; key < Key::Code::Count; key++)
		{
			Key::Code code = static_cast<Key::Code>(key);

			if (_keyboard->KeyDown(code) && !_keyPresseddMapping[code])
			{
				_keyboardMapping[action] = code;
				_updateAll = false;
				return true;
			}			
		}		
	}
	else
	{
		for (int key = 0; key < Gamepad::Button::Count; key++)
		{
			Gamepad::Button button = static_cast<Gamepad::Button>(key);

			if (_gamepad->KeyDown(button) && !_buttonPressed[button])
			{
				_gamepadMapping[action] = button;
				_updateAll = false;
				return true;
			}
		}		
	}

	return false;
}

std::string InputHelper::InputName(InputAction action)
{
	if (_mode == InputActionMode::PC)
	{
		return _nameKeyboardMapping[_keyboardMapping[action]];
	}
	else
	{
		return _nameGamepadMapping[_gamepadMapping[action]];
	}

	return "";
}

glm::vec2 InputHelper::TouchToScreen(glm::vec4 screenBound, glm::vec2 touch)
{
	float width = fabsf(screenBound.x) + fabsf(screenBound.y);
	float widthFactor = width / (float)RenderManager::Instance()->GetWidth();
	float dragX = (touch.x * widthFactor) + screenBound.x;

	float height = fabsf(screenBound.w) + fabsf(screenBound.z);
	float heightFactor = height / (float)RenderManager::Instance()->GetHeight();
	
	float dragY = 0.0f;

	if(screenBound.w < screenBound.z)
		dragY = (touch.y * heightFactor) + screenBound.w;
	else
	{
		touch.y = (float)RenderManager::Instance()->GetHeight() - touch.y;
		dragY = (touch.y * heightFactor) + screenBound.z;
	}

	return glm::vec2(dragX, dragY);
}

std::map<int, int> InputHelper::GetActionKeyMapping()
{
	std::map<int, int> _actionKeyMapping;

	for (size_t i = 0; i < InputAction::Count; i++)
	{
		InputAction action = static_cast<InputAction>(i);
		if (_mode == InputActionMode::PC)
		{
			_actionKeyMapping.insert(std::pair<int, int>(i, _keyboardMapping[action]));
		}
		else
		{
			_actionKeyMapping.insert(std::pair<int, int>(i, _gamepadMapping[action]));
		}
	}

	return _actionKeyMapping;
}


void InputHelper::SetActionKeyMapping(std::map<int, int> mapping)
{
	if (_mode == InputActionMode::PC)
	{
		_keyboardMapping.clear();
	}
	else
	{
		_gamepadMapping.clear();
	}

	typedef std::map<int, int>::iterator it_type;
	for (it_type iterator = mapping.begin(); iterator != mapping.end(); iterator++)
	{
		InputAction action = static_cast<InputAction>(iterator->first);
		
		if (_mode == InputActionMode::PC)
		{
			Key::Code code = static_cast<Key::Code>(iterator->second);
			_keyboardMapping.insert(std::pair<InputAction, Key::Code>(action, code));
		}
		else
		{

			Gamepad::Button button = static_cast<Gamepad::Button>(iterator->second);
			_gamepadMapping.insert(std::pair<InputAction, Gamepad::Button>(action, button));
		}
	}
}
