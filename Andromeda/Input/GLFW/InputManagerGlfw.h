#ifndef InputManagerGlfw_H
#define InputManagerGlfw_H

#include <Andromeda/Input/InputManager.h>
#include <GLFW/glfw3.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerGlfw : public InputManager
		{
		private:

			GLFWwindow* _window;

		public:

			void SetGlfwWindow(GLFWwindow* window);

			int GetKayboardCount();
			int GetMouseCount();
			int GetGamepadCount();
			int GetTouchDeviceCount();

			void Update();

			KeyboardDevice* GetKeyboard(int deviceNumber);
			MouseDevice* GetMouse(int deviceNumber);
			GamepadDevice* GetGamepad(int deviceNumber);
			TouchDevice* GetTouch(int deviceNumber);
		};
	}
}

#endif
