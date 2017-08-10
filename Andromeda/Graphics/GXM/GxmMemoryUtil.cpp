#include <Andromeda/Graphics/GXM/GxmMemoryUtil.h>

namespace Andromeda
{
	namespace Graphics
	{
		void *GxmMemoryUtil::AllocGpu(SceKernelMemBlockType type, unsigned int size, unsigned int alignment, SceGxmMemoryAttribFlags attribs, SceUID *uid)
		{
			void *mem;

			if (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
				size = ALIGN(size, 256 * 1024);
			}
			else {
				size = ALIGN(size, 4 * 1024);
			}

			*uid = sceKernelAllocMemBlock("gpu_mem", type, size, NULL);

			if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
				return NULL;

			if (sceGxmMapMemory(mem, size, attribs) < 0)
				return NULL;

			return mem;
		}

		void *GxmMemoryUtil::AllocVertexUsse(unsigned int size, SceUID *uid, unsigned int *usse_offset)
		{
			void *mem = NULL;

			size = ALIGN(size, 4096);
			*uid = sceKernelAllocMemBlock("vertex_usse", SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE, size, NULL);

			if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
				return NULL;
			if (sceGxmMapVertexUsseMemory(mem, size, usse_offset) < 0)
				return NULL;

			return mem;
		}

		void *GxmMemoryUtil::AllocFragmentUsse(unsigned int size, SceUID *uid, unsigned int *usse_offset)
		{
			void *mem = NULL;

			size = ALIGN(size, 4096);
			*uid = sceKernelAllocMemBlock("fragment_usse", SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE, size, NULL);

			if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
				return NULL;
			if (sceGxmMapFragmentUsseMemory(mem, size, usse_offset) < 0)
				return NULL;

			return mem;
		}

		void GxmMemoryUtil::FreeGpu(SceUID uid)
		{
			void *mem = NULL;
			if (sceKernelGetMemBlockBase(uid, &mem) < 0)
				return;
			sceGxmUnmapMemory(mem);
			sceKernelFreeMemBlock(uid);
		}

		void GxmMemoryUtil::FreeVertexUsse(SceUID uid)
		{
			void *mem = NULL;
			if (sceKernelGetMemBlockBase(uid, &mem) < 0)
				return;
			sceGxmUnmapVertexUsseMemory(mem);
			sceKernelFreeMemBlock(uid);
		}

		void GxmMemoryUtil::FreeFragmentUsse(SceUID uid)
		{
			void *mem = NULL;
			if (sceKernelGetMemBlockBase(uid, &mem) < 0)
				return;
			sceGxmUnmapFragmentUsseMemory(mem);
			sceKernelFreeMemBlock(uid);
		}
	}
}