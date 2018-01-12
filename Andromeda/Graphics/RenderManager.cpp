#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/VertexTypes.h>

#ifdef ANDROMEDA_GL3
#include <Andromeda/Graphics/GL/RenderManagerGL3.h>
#endif

#ifdef ANDROMEDA_VITA
#include <Andromeda/Graphics/GXM/RenderManagerGxm.h>
#endif

namespace Andromeda
{
	namespace Graphics
	{
		RenderManager* RenderManager::_renderManager = 0;

		RenderManager* RenderManager::Instance()
		{
			if(_renderManager == 0)
			{
				#ifdef ANDROMEDA_GL3
				{
					_renderManager = new RenderManagerGL3();
				}								
				#endif

				#ifdef ANDROMEDA_VITA
				{
					_renderManager = new RenderManagerGxm();
				}								
				#endif
			}

			return _renderManager;
		}

		RenderManager::RenderManager()
		{
			_fullScreen = false;

			_width = -1;
			_height = -1;
		}

		RenderManager::~RenderManager()
		{

		}

		size_t RenderManager::GetVertexSize(VertexType vertexType)
		{
			switch (vertexType)
			{
			case Simple:
				return sizeof(SimpleVertex);
				break;
			case Color:
				return sizeof(ColorVertex);
				break;
			case Textured:
				return sizeof(TextureVertex);
				break;
			case TextureNormal:
				return sizeof(TextureNormalVertex);
				break;
			case TextureColor:
				return sizeof(TextureColorVertex);
				break;
			case ColorNormal:
				return sizeof(ColorNormalVertex);
				break;
			case TextureColorNormal:
				return sizeof(TextureColorNormalVertex);
				break;
			}

			return 0;
		}

		int RenderManager::GetWidth()
		{
			return _width;
		}

		int RenderManager::GetHeight()
		{
			return _height;
		}

		bool RenderManager::IsFullScreen()
		{
			return _fullScreen;
		}

		void RenderManager::SetWindowSize(int width, int height)
		{
			_width = width;
			_height = height;
		}

		void RenderManager::SetFullScreen(bool state)
		{
			_fullScreen = state;
		}
	}
}
