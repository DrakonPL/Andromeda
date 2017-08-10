#include <Andromeda/Input/InputEnums.h>
#include <Andromeda/Input/GLFW/GamepadDeviceGlfw.h>
#include <vector>

namespace Andromeda
{
	namespace Input
	{
		GamepadDeviceGlfw::GamepadDeviceGlfw(GLFWwindow* window, int number)
		{
			_window = window;
			_padNumber = number;
		}

		int GamepadDeviceGlfw::LeftAnalogX()
		{
			int count;
			const float* axes = glfwGetJoystickAxes(_padNumber, &count);

			if (count > 0)
			{
				return axes[0] * 128.0f;
			}

			return 0;
		}

		int GamepadDeviceGlfw::LeftAnalogY()
		{
			int count;
			const float* axes = glfwGetJoystickAxes(_padNumber, &count);

			if (count > 1)
			{
				return axes[1] * -128.0f;
			}

			return 0;
		}

		int GamepadDeviceGlfw::RightAnalogX()
		{
			int count;
			const float* axes = glfwGetJoystickAxes(_padNumber, &count);

			if (count > 2)
			{
				return axes[2] * 128.0f;
			}

			return 0;
		}
		int GamepadDeviceGlfw::RightAnalogY()
		{
			int count;
			const float* axes = glfwGetJoystickAxes(_padNumber, &count);

			if (count > 3)
			{
				return axes[3] * -128.0f;
			}

			return 0;
		}

		bool GamepadDeviceGlfw::KeyDown(Gamepad::Button button)
		{
			int count;
			const unsigned char* buttons = glfwGetJoystickButtons(_padNumber, &count);

			switch (button)
			{
			case Gamepad::Left:
				return buttons[11];
				break;
			case Gamepad::Right:
				return buttons[10];
				break;
			case Gamepad::Up:
				return buttons[8];
				break;
			case Gamepad::Down:
				return buttons[9];
				break;
			case Gamepad::Triangle:
				return buttons[3];
				break;
			case Gamepad::Square:
				return buttons[2];
				break;
			case Gamepad::Circle:
				return buttons[1];
				break;
			case Gamepad::Cross:
				return buttons[0];
				break;
			case Gamepad::LTrigger:
				return buttons[4];
				break;
			case Gamepad::RTrigger:
				return buttons[5];
				break;
			case Gamepad::Select:
				return buttons[6];
				break;
			case Gamepad::Start:
				return buttons[7];
				break;
			}

			return false;
		}

		bool GamepadDeviceGlfw::KeyUp(Gamepad::Button button)
		{
			int count;
			const unsigned char* buttons = glfwGetJoystickButtons(_padNumber, &count);

			switch (button)
			{
			case Gamepad::Left:
				return !buttons[15];
				break;
			case Gamepad::Right:
				return !buttons[13];
				break;
			case Gamepad::Up:
				return !buttons[12];
				break;
			case Gamepad::Down:
				return !buttons[14];
				break;
			case Gamepad::Triangle:
				return !buttons[3];
				break;
			case Gamepad::Square:
				return !buttons[0];
				break;
			case Gamepad::Circle:
				return !buttons[2];
				break;
			case Gamepad::Cross:
				return !buttons[1];
				break;
			case Gamepad::LTrigger:
				return !buttons[4];
				break;
			case Gamepad::RTrigger:
				return !buttons[5];
				break;
			case Gamepad::Select:
				return !buttons[8];
				break;
			case Gamepad::Start:
				return !buttons[9];
				break;
			}

			return false;
		}

	}
}

