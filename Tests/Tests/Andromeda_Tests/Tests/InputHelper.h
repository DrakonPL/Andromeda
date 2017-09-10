#ifndef InputHelper_H
#define InputHelper_H

#include <Andromeda/Input/InputManager.h>
using namespace Andromeda::Input;

#include <glm/glm.hpp>

#include <map>
#include <string>

enum InputAction
{
	Down = 0,
	Up = 1,
	Left = 2,
	Right = 3,

	RotateLeft = 4,
	RotateRight = 5,

	Next = 6,
	Exit = 7,

	Count = 8
};

enum InputActionMode
{
	PC,
	VITA
};

class InputHelper
{
private:

	static InputHelper* _inputHelper;

	//input
	InputManager* _inputManager;

	KeyboardDevice* _keyboard;
	GamepadDevice* _gamepad;

	MouseDevice* _mouseDevice;
	TouchDevice* _touchDevice;

	InputActionMode _mode;
	bool _updateAll;

	//key state
	std::map<InputAction, bool> _actionPressed;
	std::map<Gamepad::Button, bool> _buttonPressed;
	std::map<Key::Code, bool> _keyPresseddMapping;

	//keys mapping
	std::map<InputAction, Key::Code> _keyboardMapping;
	std::map<InputAction, Gamepad::Button> _gamepadMapping;

	std::map<Gamepad::Button, std::string> _nameGamepadMapping;
	std::map<Key::Code, std::string> _nameKeyboardMapping;

	void PrepareKeyboardMapping();
	void PrepareGamepadMapping();

	void PrepareNameKeyboardMapping();
	void PrepareNameGamepadMapping();

	InputHelper();

public:

	static InputHelper* Instance();
	~InputHelper();

	void Update();
	void UpdateAllInputs(bool state);

	bool ActionPressed(InputAction action);
	bool ActionHold(InputAction action);

	int GetTouchCount();
	glm::vec2 GetTouchPosition(int touch);
	glm::vec2 TouchToScreen(glm::vec4 screenBound,glm::vec2 touch);

	bool ChangeInputForAction(InputAction action);

	std::map<int, int> GetActionKeyMapping();
	void SetActionKeyMapping(std::map<int, int> mapping);

	std::string InputName(InputAction action);
};

#endif