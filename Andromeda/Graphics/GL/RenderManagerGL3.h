#ifndef RenderManagerGL3_H
#define RenderManagerGL3_H

#include <Andromeda/Graphics/RenderManager.h>

namespace Andromeda
{
	namespace Graphics
	{
		class RenderManagerGL3 : public RenderManager
		{
		private:

			float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

			unsigned int _lastTextureId = 0;

		public:			

			RenderManagerGL3();

			void Init();
			void Finish();

			void ClearScreen();
			void SetClearColor(unsigned color);

			void StartFrame();
			void EndFrame();

			void SwapBuffers();

			void CreateTexture(Texture* image);
			void CreateEmptyTexture(Texture* image);
			void UseTexture(Texture* image);
			void DestroyTexture(Texture* image);
			void UpdateTexture(Texture* image, void *data);

			void* CreateVertices(VertexType vertexType, int size);
			VertexArrayObject* CreateVertexArrayObject(VertexType vertexType, VertexBufferDrawType drawType);

			FrameBufferObject* CreateFrameBufferObject(int width, int height);

			Shader* CreateShader();
			std::string GetVertexShaderName();
			std::string GetFragmnetShaderName();

			void SetDepth(bool state);

			void SaveDisplayBuffer(std::string fileName);
		};
	}
}

#endif
