#include <Andromeda/Input/Vita/TouchDeviceVita.h>
#include <psp2/touch.h>

namespace Andromeda
{
	namespace Input
	{
		TouchDeviceVita::TouchDeviceVita(SceTouchData* touch)
		{
			_touch = touch;
		}

		int TouchDeviceVita::GetTouchCount()
		{
			return _touch->reportNum;
		}

		int TouchDeviceVita::GetTouchX(int touch)
		{
			return _touch->report[touch].x;
		}

		int TouchDeviceVita::GetTouchY(int touch)
		{
			return _touch->report[touch].y;
		}

	}
}
