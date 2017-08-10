#ifndef TouchDeviceVita_H
#define TouchDeviceVita_H

#include <Andromeda/Input/TouchDevice.h>
#include <psp2/touch.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerVita;

		class TouchDeviceVita : public TouchDevice
		{
			SceTouchData* _touch;

			TouchDeviceVita(SceTouchData* touch);

		public:

			int GetTouchCount();

			int GetTouchX(int touch);
			int GetTouchY(int touch);

			friend class InputManagerVita;
		};
	}
}

#endif
