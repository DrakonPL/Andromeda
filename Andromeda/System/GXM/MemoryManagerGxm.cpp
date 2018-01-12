#include <Andromeda/System/GXM/MemoryManagerGxm.h>
#include <Andromeda/Graphics/GXM/GxmMemoryUtil.h>

#include <algorithm>

namespace Andromeda
{
	namespace System
	{
		void MemoryManagerGxm::AllocTexture(Graphics::Texture* texture)
		{
			if(texture->GetMipLevel() > 0)
			{
				//check if desired mip level is possible
				int width = texture->GetWidth();
				int height = texture->GetHeight();
				
				unsigned int allocationSize = 0;
				unsigned int mipcount = 0;
				
				while ((width > 1) && (height > 1) && mipcount < texture->GetMipLevel())
				{
					allocationSize += std::max(width, 8) * height * 4;
					width /= 2;
					height /= 2;
					mipcount++;
				}
				
				texture->SetMipLevel(mipcount);
			
				void* data = Graphics::GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
				allocationSize,
				SCE_GXM_TEXTURE_ALIGNMENT,
				SCE_GXM_MEMORY_ATTRIB_READ | SCE_GXM_MEMORY_ATTRIB_WRITE,
				(SceUID *)texture->GetIdPointer());

				texture->SetImageData(data);
			}else
			{
				void* data = Graphics::GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
				texture->GetWidth() * texture->GetHeight() * 4,
				SCE_GXM_TEXTURE_ALIGNMENT,
				SCE_GXM_MEMORY_ATTRIB_READ,
				(SceUID *)texture->GetIdPointer());

				texture->SetImageData(data);
			}
		}
		
		void MemoryManagerGxm::FreeTexture(Graphics::Texture* texture)
		{
			Graphics::GxmMemoryUtil::FreeGpu((SceUID)texture->GetId());
		}
	}
}


