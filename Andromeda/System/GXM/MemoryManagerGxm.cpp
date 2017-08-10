#include <Andromeda/System/GXM/MemoryManagerGxm.h>
#include <Andromeda/Graphics/GXM/GxmMemoryUtil.h>

namespace Andromeda
{
	namespace System
	{
		void MemoryManagerGxm::AllocTexture(Graphics::Texture* texture)
		{
			void* data = Graphics::GxmMemoryUtil::AllocGpu(
				SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
				texture->GetWidth() * texture->GetHeight() * 4,
				SCE_GXM_TEXTURE_ALIGNMENT,
				SCE_GXM_MEMORY_ATTRIB_READ,
				(SceUID *)texture->GetIdPointer());

			texture->SetImageData(data);
		}

		void MemoryManagerGxm::FreeTexture(Graphics::Texture* texture)
		{
			Graphics::GxmMemoryUtil::FreeGpu((SceUID)texture->GetId());
			texture->SetImageData(0);
		}
	}
}


