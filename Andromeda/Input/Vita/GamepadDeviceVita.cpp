#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/Vita/GamepadDeviceVita.h>
#include <psp2/ctrl.h>

namespace Andromeda
{
	namespace Input
	{
		GamepadDeviceVita::GamepadDeviceVita(SceCtrlData* pad)
		{
			_pad = pad;
		}

		int GamepadDeviceVita::LeftAnalogX()
		{
			return _pad->lx - 128;
		}
		int GamepadDeviceVita::LeftAnalogY()
		{
			return _pad->ly - 128;
		}

		int GamepadDeviceVita::RightAnalogX()
		{
			return _pad->rx - 128;
		}
		int GamepadDeviceVita::RightAnalogY()
		{
			return _pad->ry - 128;
		}

		bool GamepadDeviceVita::KeyDown(Gamepad::Button button)
		{
			switch(button)
			{
			case Gamepad::Left: 
				return _pad->buttons & SCE_CTRL_LEFT;
				break;
			case Gamepad::Right: 
				return _pad->buttons & SCE_CTRL_RIGHT;
				break;
			case Gamepad::Up: 
				return _pad->buttons & SCE_CTRL_UP;
				break;
			case Gamepad::Down: 
				return _pad->buttons & SCE_CTRL_DOWN;
				break;
			case Gamepad::Triangle: 
				return _pad->buttons & SCE_CTRL_TRIANGLE;
				break;
			case Gamepad::Square: 
				return _pad->buttons & SCE_CTRL_SQUARE;
				break;
			case Gamepad::Circle: 
				return _pad->buttons & SCE_CTRL_CIRCLE;
				break;
			case Gamepad::Cross: 
				return _pad->buttons & SCE_CTRL_CROSS;
				break;
			case Gamepad::LTrigger:
				return _pad->buttons & SCE_CTRL_LTRIGGER;
				break;
			case Gamepad::RTrigger:
				return _pad->buttons & SCE_CTRL_RTRIGGER;
				break;
			case Gamepad::Select:
				return _pad->buttons & SCE_CTRL_SELECT;
				break;
			case Gamepad::Start:
				return _pad->buttons & SCE_CTRL_START;
				break;
			}

			return false;
		}

		bool GamepadDeviceVita::KeyUp(Gamepad::Button button)
		{
			switch (button)
			{
			case Gamepad::Left:
				return !(_pad->buttons & SCE_CTRL_LEFT);
				break;
			case Gamepad::Right:
				return !(_pad->buttons & SCE_CTRL_RIGHT);
				break;
			case Gamepad::Up:
				return !(_pad->buttons & SCE_CTRL_UP);
				break;
			case Gamepad::Down:
				return !(_pad->buttons & SCE_CTRL_DOWN);
				break;
			case Gamepad::Triangle:
				return !(_pad->buttons & SCE_CTRL_TRIANGLE);
				break;
			case Gamepad::Square:
				return !(_pad->buttons & SCE_CTRL_SQUARE);
				break;
			case Gamepad::Circle:
				return !(_pad->buttons & SCE_CTRL_CIRCLE);
				break;
			case Gamepad::Cross:
				return !(_pad->buttons & SCE_CTRL_CROSS);
				break;
			case Gamepad::LTrigger:
				return !(_pad->buttons & SCE_CTRL_LTRIGGER);
				break;
			case Gamepad::RTrigger:
				return !(_pad->buttons & SCE_CTRL_RTRIGGER);
				break;
			case Gamepad::Select:
				return !(_pad->buttons & SCE_CTRL_SELECT);
				break;
			case Gamepad::Start:
				return !(_pad->buttons & SCE_CTRL_START);
				break;
			}

			return false;
		}

	}
}

