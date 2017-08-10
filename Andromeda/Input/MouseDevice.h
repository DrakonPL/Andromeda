#ifndef MouseDevice_H
#define MouseDevice_H

#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/InputDevice.h>

namespace Andromeda
{
	namespace Input
	{
		class InputMager;

		class MouseDevice : public InputDevice
		{
		protected:

			MouseDevice(){}

		public:

			virtual bool ButtonDown(Mouse::Button button) = 0;
			virtual bool ButtonUp(Mouse::Button button) = 0;

			virtual int GetPosX() = 0;
			virtual int GetPosY() = 0;

			virtual void SetPos(int x,int y) = 0;

			virtual void SetCursorVisible(bool state) = 0;

			friend class InputMager;
		};
	}
}

#endif
