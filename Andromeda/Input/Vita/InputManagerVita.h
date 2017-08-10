#ifndef InputManagerVita_H
#define InputManagerVita_H

#include <Andromeda/Input/InputManager.h>

#include <psp2/ctrl.h>
#include <psp2/touch.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerVita : public InputManager
		{
			SceCtrlData     _pad;
			SceTouchData    _frontTouch;
			SceTouchData    _backTouch;

		public:

			int GetKayboardCount();
			int GetMouseCount();
			int GetGamepadCount();
			int GetTouchDeviceCount();

			void Update();

			KeyboardDevice* GetKeyboard(int deviceNumber);
			MouseDevice* GetMouse(int deviceNumber);
			GamepadDevice* GetGamepad(int deviceNumber);
			TouchDevice* GetTouch(int deviceNumber);
		};
	}
}

#endif
