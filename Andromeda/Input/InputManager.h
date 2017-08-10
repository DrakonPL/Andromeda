#ifndef InputManager_H
#define InputManager_H

#include <Andromeda/Input/KeyboardDevice.h>
#include <Andromeda/Input/MouseDevice.h>
#include <Andromeda/Input/GamepadDevice.h>
#include <Andromeda/Input/TouchDevice.h>

#include <string>
#include <map>

namespace Andromeda
{
	namespace Input
	{
		class InputManager
		{
		protected:

			std::map<std::string, InputDevice*> _devices;

			static InputManager* _inputManager;

			InputManager();

		protected:

			virtual KeyboardDevice* GetKeyboard(int deviceNumber) = 0;
			virtual MouseDevice* GetMouse(int deviceNumber) = 0;
			virtual GamepadDevice* GetGamepad(int deviceNumber) = 0;
			virtual TouchDevice* GetTouch(int deviceNumber) = 0;

		public:

			static InputManager* Instance();

			virtual int GetKayboardCount() = 0;
			virtual int GetMouseCount() = 0;
			virtual int GetGamepadCount() = 0;
			virtual int GetTouchDeviceCount() = 0;

			virtual void Update() = 0;

			KeyboardDevice* GetKeyboardDevice(int deviceNumber);
			MouseDevice* GetMouseDevice(int deviceNumber);
			GamepadDevice* GetGamepadDevice(int deviceNumber);
			TouchDevice* GetTouchDevice(int deviceNumber);
		};
	}
}

#endif
