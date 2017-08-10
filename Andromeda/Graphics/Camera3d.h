#ifndef Camera3d_H
#define Camera3d_H

#include <Andromeda/Graphics/GraphicsEnums.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Andromeda
{
	namespace Graphics
	{
		class Camera3d
		{
		public:

			enum CameraMovementEnum
			{
				FORWARD,
				BACKWARD,
				LEFT,
				RIGHT
			};

			// Default camera values
			float YAW = -90.0f;
			float PITCH = 0.0f;
			float SPEED = 3.0f;
			float SENSITIVTY = 0.25f;
			float ZOOM = 45.0f;

			// Camera Attributes
			glm::vec3 Position;
			glm::vec3 Front;
			glm::vec3 Up;
			glm::vec3 Right;
			glm::vec3 WorldUp;

			// Eular Angles
			float Yaw;
			float Pitch;

			// Camera options
			float MovementSpeed;
			float MouseSensitivity;
			float Zoom;

			Camera3d(glm::vec3 position , glm::vec3 up , float yaw , float pitch);
			Camera3d(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

			glm::mat4 GetViewMatrix();

			void ProcessKeyboard(CameraMovementEnum direction, float deltaTime);
			void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
			void ProcessMouseScroll(float yoffset);

			void UpdateCameraVectors();
		};
	}
}

#endif
