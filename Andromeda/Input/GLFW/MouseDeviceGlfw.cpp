#include <Andromeda/Input/GLFW/MouseDeviceGlfw.h>

namespace Andromeda
{
	namespace Input
	{
		MouseDeviceGlfw::MouseDeviceGlfw(GLFWwindow* window)
		{
			_window = window;
		}

		bool MouseDeviceGlfw::ButtonDown(Mouse::Button button)
		{
			if (glfwGetMouseButton(_window, button) == GLFW_PRESS)
				return true;

			return false;
		}

		bool MouseDeviceGlfw::ButtonUp(Mouse::Button button)
		{
			if (glfwGetMouseButton(_window, button) == GLFW_RELEASE)
				return true;

			return false;
		}

		int MouseDeviceGlfw::GetPosX()
		{
			double xpos, ypos;
			glfwGetCursorPos(_window, &xpos, &ypos);
			return xpos;
		}

		int MouseDeviceGlfw::GetPosY()
		{
			double xpos, ypos;
			glfwGetCursorPos(_window, &xpos, &ypos);
			return ypos;
		}

		void MouseDeviceGlfw::SetPos(int x, int y)
		{
			glfwSetCursorPos(_window, x, y);
		}

		void MouseDeviceGlfw::SetCursorVisible(bool state)
		{
			if(!state)
			{
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			else
			{
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}

	}
}

