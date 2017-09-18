#include <Andromeda/Graphics/GL/FrameBufferObjectGL3.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/RenderManager.h>

#define GLEW_STATIC
#include <GL/glew.h>

namespace Andromeda
{
	namespace Graphics
	{
		FrameBufferObjectGL3::FrameBufferObjectGL3(int width, int height)
		{
			_width = width;
			_height = height;

			PrepareBuffer();
		}

		FrameBufferObjectGL3::~FrameBufferObjectGL3()
		{
			glDeleteFramebuffers(1, &_frameBuffer);
			glDeleteRenderbuffers(1, &_renderBuffer);
			
			TextureManager::Instance()->Remove(_texture);
		}

		void FrameBufferObjectGL3::PrepareBuffer()
		{
			//create texture
			_texture = TextureManager::Instance()->CreateEmpty("", _width, _height, TextureFilerType::LinearFilter);
			RenderManager::Instance()->CreateEmptyTexture(_texture);

			//create render buffer
			glGenRenderbuffers(1, &_renderBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
			// Use a single render buffer object for both a depth AND stencil buffer.
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
			//bind default render buffer
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			//create frame buffer
			glGenFramebuffers(1, &_frameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);			

			//texture attachment
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->GetId(), 0);
						
			// Now actually attach it
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer); 
														
			// Now that we actually created the frame buffer and added all attachments we want to check if it is actually complete now
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				//cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
			}
			
			//bind default frame buffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void FrameBufferObjectGL3::Bind()
		{
			glViewport(0, 0, _width, _height);

			glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
		}

		void FrameBufferObjectGL3::UnBind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glViewport(0, 0, RenderManager::Instance()->GetWidth(), RenderManager::Instance()->GetHeight());
		}
	}
}
