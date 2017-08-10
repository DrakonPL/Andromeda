#include <Andromeda/Graphics/GL/RenderManagerGL3.h>
#include <Andromeda/Graphics/GL/FrameBufferObjectGL3.h>
#include <Andromeda/Graphics/GL/VertexBufferObjectGL3.h>
#include <Andromeda/Graphics/GL/VertexArrayObjectGL3.h>
#include <Andromeda/Graphics/GL/ShaderGlsl.h>
#include <Andromeda/Graphics/VertexTypes.h>

#define GLEW_STATIC
#include <GL/glew.h>


namespace Andromeda
{
	namespace Graphics
	{
		RenderManagerGL3::RenderManagerGL3() : RenderManager()
		{
			
		}

		void RenderManagerGL3::Init()
		{
			glewExperimental = GL_TRUE;

			//init glwe lib
			glewInit();

			// Define the viewport dimensions
			glViewport(0, 0, _width, _height);

			// Setup OpenGL options
			glEnable(GL_DEPTH_TEST);

			//enable blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//glEnable(GL_CULL_FACE);
			//glCullFace(GL_BACK);
			//glFrontFace(GL_CCW);

			clearColor[0] = 0.2f;
			clearColor[1] = 0.3f;
			clearColor[2] = 0.3f;
			clearColor[3] = 1.0f;
		}

		void RenderManagerGL3::Finish()
		{
			
		}

		void RenderManagerGL3::ClearScreen()
		{
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void RenderManagerGL3::SetClearColor(unsigned color)
		{
			clearColor[0] = ((color >> 8 * 0) & 0xFF) / 255.0f;
			clearColor[1] = ((color >> 8 * 1) & 0xFF) / 255.0f;
			clearColor[2] = ((color >> 8 * 2) & 0xFF) / 255.0f;
			clearColor[3] = ((color >> 8 * 3) & 0xFF) / 255.0f;
		}

		void RenderManagerGL3::StartFrame()
		{
			
		}

		void RenderManagerGL3::EndFrame()
		{
			
		}

		void RenderManagerGL3::SwapBuffers()
		{
			
		}

		void RenderManagerGL3::CreateTexture(Texture* image)
		{
			if(image != 0)
			{
				glGenTextures(1, image->GetIdPointer());

				// All upcoming GL_TEXTURE_2D operations now have effect on this texture object
				glBindTexture(GL_TEXTURE_2D, image->GetId());
				
				// Set the texture wrapping parameters
				// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				// Set texture filtering parameters
				if (image->GetFilterType() == TextureFilerType::LinearFilter)
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				}

				int textureFormat = GL_RGBA;

				switch (image->GetColorType())
				{
				case TextureColorType::Texture_RGB:
					textureFormat = GL_RGB;
					break;
				case TextureColorType::Texture_RGBA:
					textureFormat = GL_RGBA;
					break;
				default:
					textureFormat = GL_RGBA;
					break;
				}

				glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, image->GetWidth(), image->GetHeight(), 0, textureFormat, GL_UNSIGNED_BYTE, image->GetImageData());
				//glGenerateMipmap(GL_TEXTURE_2D);

				// Unbind texture when done, so we won't accidentily mess up our texture.
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void RenderManagerGL3::CreateEmptyTexture(Texture* image)
		{
			if (image != 0)
			{
				glGenTextures(1, image->GetIdPointer());

				// All upcoming GL_TEXTURE_2D operations now have effect on this texture object
				glBindTexture(GL_TEXTURE_2D, image->GetId());

				// Set the texture wrapping parameters
				// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				// Set texture filtering parameters
				if (image->GetFilterType() == TextureFilerType::LinearFilter)
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				}

				int textureFormat = GL_RGBA;

				switch (image->GetColorType())
				{
				case TextureColorType::Texture_RGB:
					textureFormat = GL_RGB;
					break;
				case TextureColorType::Texture_RGBA:
					textureFormat = GL_RGBA;
					break;
				default:
					textureFormat = GL_RGBA;
					break;
				}

				glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, image->GetWidth(), image->GetHeight(), 0, textureFormat, GL_UNSIGNED_BYTE, 0);

				// Unbind texture when done, so we won't accidentily mess up our texture.
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void RenderManagerGL3::DestroyTexture(Texture* image)
		{
			if (image != 0)
			{
				glDeleteTextures(1, image->GetIdPointer());
			}
		}

		void RenderManagerGL3::UseTexture(Texture* image)
		{
			if(image != 0 && _lastTextureId != image->GetId())
			{
				glBindTexture(GL_TEXTURE_2D, image->GetId());
				_lastTextureId = image->GetId();
			}
		}

		void RenderManagerGL3::UpdateTexture(Texture* image, void *data)
		{
			if (image != 0)
			{
				int textureFormat = GL_RGBA;

				switch (image->GetColorType())
				{
				case TextureColorType::Texture_RGB:
					textureFormat = GL_RGB;
					break;
				case TextureColorType::Texture_RGBA:
					textureFormat = GL_RGBA;
					break;
				default:
					textureFormat = GL_RGBA;
					break;
				}

				UseTexture(image);
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->GetWidth(), image->GetHeight(), textureFormat, GL_UNSIGNED_BYTE, data);
			}
		}

		void* RenderManagerGL3::CreateVertices(VertexType vertexType, int size)
		{
			switch (vertexType)
			{
			case Simple:
				return new SimpleVertex[size];
				break;
			case Color:
				return new ColorVertex[size];
				break;
			case Textured:
				return new TextureVertex[size];
				break;
			case TextureNormal:
				return new TextureNormalVertex[size];
				break;
			case TextureColor:
				return new TextureColorVertex[size];
				break;
			case ColorNormal:
				return new ColorNormalVertex[size];
				break;
			case TextureColorNormal:
				return new TextureColorVertex[size];
				break;
			default: break;
			}

			return 0;
		}		

		VertexArrayObject* RenderManagerGL3::CreateVertexArrayObject(VertexType vertexType, VertexBufferDrawType drawType)
		{
			VertexArrayObjectGL3* _vertexArray = new VertexArrayObjectGL3();

			//set basic info
			_vertexArray->SetVertexBufferDrawType(drawType);
			_vertexArray->SetVertexType(vertexType);
			_vertexArray->SetVertexPrimitive(Triangle);

			return _vertexArray;
		}

		FrameBufferObject*  RenderManagerGL3::CreateFrameBufferObject(int width, int height)
		{
			FrameBufferObjectGL3* fbo = new FrameBufferObjectGL3(width, height);


			return fbo;
		}

		Shader* RenderManagerGL3::CreateShader()
		{
			return new ShaderGlSl();
		}

		std::string RenderManagerGL3::GetVertexShaderName()
		{
			return ".vert";
		}

		std::string RenderManagerGL3::GetFragmnetShaderName()
		{
			return ".frag";
		}

		void RenderManagerGL3::SetDepth(bool state)
		{
			if (state)
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}

		void RenderManagerGL3::SaveDisplayBuffer(std::string fileName)
		{

		}
	}
}
