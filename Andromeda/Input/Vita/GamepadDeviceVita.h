#ifndef GamepadDeviceVita_H
#define GamepadDeviceVita_H

#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/GamepadDevice.h>
#include <psp2/ctrl.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerVita;

		class GamepadDeviceVita : public GamepadDevice
		{
			SceCtrlData* _pad;

			GamepadDeviceVita(SceCtrlData* pad);

		public:

			int LeftAnalogX();
			int LeftAnalogY();

			int RightAnalogX();
			int RightAnalogY();

			bool KeyDown(Gamepad::Button button);
			bool KeyUp(Gamepad::Button button);

			friend class InputManagerVita;

		};
	}
}

#endif
