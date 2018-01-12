#include <Andromeda/Graphics/GXM/GxmMemoryUtil.h>
#include <Andromeda/Utils/Logger.h>



namespace Andromeda
{
	namespace Graphics
	{
		long GxmMemoryUtil::_gpuMem = 0;
		
		void *GxmMemoryUtil::AllocGpu(SceKernelMemBlockType type, unsigned int size, unsigned int alignment, SceGxmMemoryAttribFlags attribs, SceUID *uid)
		{
			void *mem;

			if (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
				size = ALIGN(size, 256 * 1024);
			}
			else {
				size = ALIGN(size, 4 * 1024);
			}
			
			_gpuMem+=size;
			
			Utils::Logger::Instance()->Log("AllocGpu: %d Total: %ld\n",size,_gpuMem);

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
			_gpuMem+=size;
			
			Utils::Logger::Instance()->Log("AllocVertexUsse: %d Total: %ld\n",size,_gpuMem);
			
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
			_gpuMem+=size;
			
			Utils::Logger::Instance()->Log("AllocFragmentUsse: %d Total: %ld\n",size,_gpuMem);
			
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
			
			SceKernelMemBlockInfo Info;
			Info.size = sizeof(Info);
			sceKernelGetMemBlockInfoByAddr(mem, &Info);
			
			_gpuMem-=Info.mappedSize;
			
			Utils::Logger::Instance()->Log("FreeGpu: %d Total: %ld\n",Info.mappedSize,_gpuMem);
			
			sceGxmUnmapMemory(mem);
			sceKernelFreeMemBlock(uid);
		}

		void GxmMemoryUtil::FreeVertexUsse(SceUID uid)
		{
			void *mem = NULL;
			if (sceKernelGetMemBlockBase(uid, &mem) < 0)
				return;
			
			SceKernelMemBlockInfo Info;
			Info.size = sizeof(Info);
			sceKernelGetMemBlockInfoByAddr(mem, &Info);
			
			_gpuMem-=Info.mappedSize;
			
			Utils::Logger::Instance()->Log("FreeVertexUsse: %d Total: %ld\n",Info.mappedSize,_gpuMem);
			
			sceGxmUnmapVertexUsseMemory(mem);
			sceKernelFreeMemBlock(uid);
		}

		void GxmMemoryUtil::FreeFragmentUsse(SceUID uid)
		{
			void *mem = NULL;
			if (sceKernelGetMemBlockBase(uid, &mem) < 0)
				return;
			
			SceKernelMemBlockInfo Info;
			Info.size = sizeof(Info);
			sceKernelGetMemBlockInfoByAddr(mem, &Info);
			
			_gpuMem-=Info.mappedSize;
			
			Utils::Logger::Instance()->Log("FreeFragmentUsse: %d Total: %ld\n",Info.mappedSize,_gpuMem);
			
			sceGxmUnmapFragmentUsseMemory(mem);
			sceKernelFreeMemBlock(uid);
		}
	}
}