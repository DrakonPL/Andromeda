#ifndef MouseDeviceGlfw_H
#define MouseDeviceGlfw_H

#include <Andromeda/Input/MouseDevice.h>

#include <GLFW/glfw3.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerGlfw;

		class MouseDeviceGlfw : public MouseDevice
		{

			GLFWwindow* _window;

		protected:

			MouseDeviceGlfw(GLFWwindow* window);

		public:

			bool ButtonDown(Mouse::Button button);
			bool ButtonUp(Mouse::Button button);

			int GetPosX();
			int GetPosY();

			void SetPos(int x, int y);

			void SetCursorVisible(bool state);

			friend class InputManagerGlfw;
		};
		
	}
}

#endif
