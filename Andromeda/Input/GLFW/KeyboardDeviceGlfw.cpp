#include <Andromeda/Input/GLFW/KeyboardDeviceGlfw.h>
#include <GLFW/glfw3.h>

namespace Andromeda
{
	namespace Input
	{
		KeyboardDeviceGlfw::KeyboardDeviceGlfw(GLFWwindow* window)
		{
			_window = window;
		}

		bool KeyboardDeviceGlfw::KeyDown(Key::Code key)
		{
			if (glfwGetKey(_window, key) == GLFW_PRESS)
				return true;

			return false;
		}

		bool KeyboardDeviceGlfw::KeyUp(Key::Code key)
		{
			if (glfwGetKey(_window, key) == GLFW_RELEASE)
				return true;

			return false;
		}
	}
}
