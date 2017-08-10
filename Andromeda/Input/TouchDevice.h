#ifndef TouchDevice_H
#define TouchDevice_H

#include <Andromeda/Input/InputDevice.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManager;

		class TouchDevice : public InputDevice
		{
		protected:

			TouchDevice(){}

		public:

			virtual int GetTouchCount() = 0;

			virtual int GetTouchX(int touch) = 0;
			virtual int GetTouchY(int touch) = 0;

			friend class InputManager;
		};
	}
}

#endif
