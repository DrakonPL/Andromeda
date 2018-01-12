#ifndef GxmMemoryUtil_H
#define GxmMemoryUtil_H

#include <psp2/gxm.h>
#include <psp2/types.h>
#include <psp2/kernel/sysmem.h>

#define ALIGN(x, a)	(((x) + ((a) - 1)) & ~((a) - 1))
#define	UNUSED(a)	(void)(a)

namespace Andromeda
{
	namespace Graphics
	{
		class GxmMemoryUtil
		{
		private:
			
			static  long _gpuMem;
			
		public:

			static void *AllocGpu(SceKernelMemBlockType type, unsigned int size, unsigned int alignment, SceGxmMemoryAttribFlags attribs, SceUID *uid);
			static void FreeGpu(SceUID uid);
			
			static void *AllocVertexUsse(unsigned int size, SceUID *uid, unsigned int *usse_offset);
			static void FreeVertexUsse(SceUID uid);

			static void *AllocFragmentUsse(unsigned int size, SceUID *uid, unsigned int *usse_offset);			
			static void FreeFragmentUsse(SceUID uid);
		};
	}
}

#endif
