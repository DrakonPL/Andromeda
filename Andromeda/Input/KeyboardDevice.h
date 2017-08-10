#ifndef KeyboardDevice_H
#define KeyboardDevice_H

#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/InputDevice.h>

namespace Andromeda
{
	namespace Input
	{
		class InputMager;

		class KeyboardDevice : public InputDevice
		{
		protected:

			KeyboardDevice(){}

		public:

			virtual bool KeyDown(Key::Code key) = 0;
			virtual bool KeyUp(Key::Code key) = 0;

			friend class InputMager;
		};
	}
}

#endif
