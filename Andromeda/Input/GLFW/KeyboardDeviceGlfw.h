#ifndef KeyboardDeviceGlfw_H
#define KeyboardDeviceGlfw_H

#include <Andromeda/Input/KeyboardDevice.h>
#include <GLFW/glfw3.h>

namespace Andromeda
{
	namespace Input
	{
		class InputManagerGlfw;

		class KeyboardDeviceGlfw : public KeyboardDevice
		{
		protected:

			GLFWwindow* _window;

			KeyboardDeviceGlfw(GLFWwindow* window);

		public:

			bool KeyDown(Key::Code key);
			bool KeyUp(Key::Code key);

			friend class InputManagerGlfw;
		};

	}
}

#endif
