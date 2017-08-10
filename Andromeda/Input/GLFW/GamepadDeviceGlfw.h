#ifndef GamepadDeviceVita_H
#define GamepadDeviceVita_H

#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/GamepadDevice.h>
#include <GLFW/glfw3.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerGlfw;

		class GamepadDeviceGlfw : public GamepadDevice
		{
			GLFWwindow* _window;
			int _padNumber;

			GamepadDeviceGlfw(GLFWwindow* window,int number);

		public:

			int LeftAnalogX();
			int LeftAnalogY();

			int RightAnalogX();
			int RightAnalogY();

			bool KeyDown(Gamepad::Button button);
			bool KeyUp(Gamepad::Button button);

			friend class InputManagerGlfw;

		};
	}
}

#endif
