#include <Andromeda/Input/InputManager.h>

#ifdef ANDROMEDA_GLFW
#include <Andromeda/Input/GLFW/InputManagerGlfw.h>
#endif

#ifdef ANDROMEDA_VITA
#include <Andromeda/Input/Vita/InputManagerVita.h>
#endif

#ifdef ANDROMEDA_RPI
#include <Andromeda/Input/RPI/InputManagerRpi.h>
#endif

namespace Andromeda
{
	namespace Input
	{
		InputManager* InputManager::_inputManager = 0;

		InputManager::InputManager()
		{
			
		}

		InputManager* InputManager::Instance()
		{
			if(_inputManager == 0)
			{
				#ifdef ANDROMEDA_GLFW
				{
					_inputManager = new InputManagerGlfw();
				}
				#endif

				#ifdef ANDROMEDA_VITA
				{
					_inputManager = new InputManagerVita();
				}
				#endif
				
				#ifdef ANDROMEDA_RPI
				{
					_inputManager = new InputManagerRpi();
				}
				#endif
			}

			return _inputManager;
		}

		KeyboardDevice* InputManager::GetKeyboardDevice(int deviceNumber)
		{
			std::string deviceName = "keyboard" + deviceNumber;

			if (_devices.find(deviceName) == _devices.end())
			{
				KeyboardDevice* device = _inputManager->GetKeyboard(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<KeyboardDevice*>(_devices[deviceName]);
			}
		}

		MouseDevice* InputManager::GetMouseDevice(int deviceNumber)
		{
			std::string deviceName = "mouse" + deviceNumber;

			if (_devices.find(deviceName) == _devices.end())
			{
				MouseDevice* device = _inputManager->GetMouse(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<MouseDevice*>(_devices[deviceName]);
			}
		}

		GamepadDevice* InputManager::GetGamepadDevice(int deviceNumber)
		{
			std::string deviceName = "gamepad" + deviceNumber;

			if (_devices.find(deviceName) == _devices.end())
			{
				GamepadDevice* device = _inputManager->GetGamepad(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<GamepadDevice*>(_devices[deviceName]);
			}
		}

		TouchDevice* InputManager::GetTouchDevice(int deviceNumber)
		{
			std::string deviceName = "touch" + deviceNumber;

			if (_devices.find(deviceName) == _devices.end())
			{
				TouchDevice* device = _inputManager->GetTouch(deviceNumber);

				_devices.insert(std::pair<std::string, InputDevice*>(deviceName, device));

				return device;
			}
			else
			{
				return static_cast<TouchDevice*>(_devices[deviceName]);
			}
		}

	}
}

