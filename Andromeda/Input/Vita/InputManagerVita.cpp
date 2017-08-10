#include <Andromeda/Input/Vita/InputManagerVita.h>
#include <Andromeda/Input/Vita/GamepadDeviceVita.h>
#include <Andromeda/Input/Vita/TouchDeviceVita.h>

namespace Andromeda
{
	namespace Input
	{
		int InputManagerVita::GetKayboardCount()
		{
			return 0;
		}

		int InputManagerVita::GetMouseCount()
		{
			return 0;
		}

		int InputManagerVita::GetGamepadCount()
		{
			return 1;
		}

		int InputManagerVita::GetTouchDeviceCount()
		{
			return 2;
		}

		void InputManagerVita::Update()
		{
			sceCtrlPeekBufferPositive(0, &_pad, 1);
			sceTouchPeek(SCE_TOUCH_PORT_FRONT, &_frontTouch, 1);
			sceTouchPeek(SCE_TOUCH_PORT_BACK, &_backTouch, 1);
		}

		KeyboardDevice* InputManagerVita::GetKeyboard(int deviceNumber)
		{
			return 0;
		}

		MouseDevice* InputManagerVita::GetMouse(int deviceNumber)
		{
			return 0;
		}

		GamepadDevice* InputManagerVita::GetGamepad(int deviceNumber)
		{
			return new GamepadDeviceVita(&_pad);
		}

		TouchDevice* InputManagerVita::GetTouch(int deviceNumber)
		{
			if(deviceNumber == 0)
			{
				return new TouchDeviceVita(&_frontTouch);
			}
			else if(deviceNumber == 1)
			{
				return new TouchDeviceVita(&_backTouch);
			}

			return 0;
		}
	}
}
