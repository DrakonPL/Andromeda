#include <Andromeda/Graphics/GXM/ShaderGxm.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <Andromeda/Utils/Logger.h>

namespace Andromeda
{
	namespace Graphics
	{
		ShaderGxm::ShaderGxm() : Shader()
		{
			
		}

		ShaderGxm::~ShaderGxm()
		{
			sceGxmShaderPatcherReleaseFragmentProgram(_shaderPatcher, _fragmentProgram);
			sceGxmShaderPatcherReleaseVertexProgram(_shaderPatcher, _vertexProgram);

			sceGxmShaderPatcherUnregisterProgram(_shaderPatcher, _fragmentProgramId);
			sceGxmShaderPatcherUnregisterProgram(_shaderPatcher, _vertexProgramId);
		}

		void ShaderGxm::LoadFromFile(std::string vertexFile, std::string fragmentFile, VertexType vertexType)
		{
			_vertexType = vertexType;

			//load vertex shader
			LoadShaderFile(vertexFile,VertexShader);

			//load fragment shader
			LoadShaderFile(fragmentFile,FragmentShader);

			//link program
			LinkShader();
		}

		void ShaderGxm::LoadFromMemory(std::string vertexShader, std::string fragmentShader, VertexType vertexType)
		{
			_vertexType = vertexType;
		}

		unsigned int ShaderGxm::LoadShaderFile(std::string fileName, ShaderType shaderType)
		{
			FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(fileName);

			if (!file->Exist())
			{
				Utils::Logger::Instance()->Log("Can't open %s\n", fileName.c_str());
				return -1;
			}				

			file->Open(FileSystem::Read, FileSystem::Binary);

			int size = 0;

			if (shaderType == VertexShader)
			{
				_gxmVertexProgram = (SceGxmProgram*)file->GetData(size);
			}
			else
			{
				_gxmFragmentProgram = (SceGxmProgram*)file->GetData(size);
			}

			file->Close();

			if(shaderType == VertexShader)
			{
				// check the shaders
				sceGxmProgramCheck(_gxmVertexProgram);

				// register programs with the patcher
				sceGxmShaderPatcherRegisterProgram(_shaderPatcher, _gxmVertexProgram, &_vertexProgramId);
			}else
			{
				// check the shaders
				sceGxmProgramCheck(_gxmFragmentProgram);

				// register programs with the patcher
				sceGxmShaderPatcherRegisterProgram(_shaderPatcher, _gxmFragmentProgram, &_fragmentProgramId);
			}

		}

		unsigned int ShaderGxm::LinkShader()
		{
			SceGxmVertexAttribute *vertexArrtibs;
			SceGxmVertexStream *vertexstream;
			int paramsCount = 0;

			switch (_vertexType)
			{
			case Andromeda::Graphics::Simple:
			{
				paramsCount = 1;
				
				vertexArrtibs = new SceGxmVertexAttribute[paramsCount];
				vertexstream = new SceGxmVertexStream[1];

				//get attribute index
				const SceGxmProgramParameter *paramClearPositionAttribute = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iPosition");

				//create clear vertex format
				vertexArrtibs[0].streamIndex = 0;
				vertexArrtibs[0].offset = 0;
				vertexArrtibs[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[0].componentCount = 3;
				vertexArrtibs[0].regIndex = sceGxmProgramParameterGetResourceIndex(paramClearPositionAttribute);

			
				vertexstream[0].stride = sizeof(SimpleVertex);
				vertexstream[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;
			}
				break;
			case Andromeda::Graphics::Color:
			{
				paramsCount = 2;

				vertexArrtibs = new SceGxmVertexAttribute[paramsCount];
				vertexstream = new SceGxmVertexStream[1];

				//get attribute index
				const SceGxmProgramParameter *positionParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iPosition");
				const SceGxmProgramParameter *colorParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iColor");

				//position param
				vertexArrtibs[0].streamIndex = 0;
				vertexArrtibs[0].offset = 0;
				vertexArrtibs[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[0].componentCount = 3;
				vertexArrtibs[0].regIndex = sceGxmProgramParameterGetResourceIndex(positionParam);

				//color param
				vertexArrtibs[1].streamIndex = 0;
				vertexArrtibs[1].offset = 12;
				vertexArrtibs[1].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[1].componentCount = 3;
				vertexArrtibs[1].regIndex = sceGxmProgramParameterGetResourceIndex(colorParam);


				vertexstream[0].stride = sizeof(ColorVertex);
				vertexstream[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;
			}
				break;
			case Andromeda::Graphics::Textured:
			{
				paramsCount = 2;

				vertexArrtibs = new SceGxmVertexAttribute[paramsCount];
				vertexstream = new SceGxmVertexStream[1];

				//get attribute index
				const SceGxmProgramParameter *positionParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iPosition");
				const SceGxmProgramParameter *textureParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iTexCoord");

				//position param
				vertexArrtibs[0].streamIndex = 0;
				vertexArrtibs[0].offset = 0;
				vertexArrtibs[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[0].componentCount = 3;
				vertexArrtibs[0].regIndex = sceGxmProgramParameterGetResourceIndex(positionParam);

				//texture param
				vertexArrtibs[1].streamIndex = 0;
				vertexArrtibs[1].offset = 12;
				vertexArrtibs[1].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[1].componentCount = 2;
				vertexArrtibs[1].regIndex = sceGxmProgramParameterGetResourceIndex(textureParam);

				vertexstream[0].stride = sizeof(TextureVertex);
				vertexstream[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;
			}
				break;
			case Andromeda::Graphics::TextureNormal:
			{
				paramsCount = 3;

				vertexArrtibs = new SceGxmVertexAttribute[paramsCount];
				vertexstream = new SceGxmVertexStream[1];

				//get attribute index
				const SceGxmProgramParameter *positionParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iPosition");
				const SceGxmProgramParameter *colorParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iNormal");
				const SceGxmProgramParameter *textureParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iTexCoord");

				//position param
				vertexArrtibs[0].streamIndex = 0;
				vertexArrtibs[0].offset = 0;
				vertexArrtibs[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[0].componentCount = 3;
				vertexArrtibs[0].regIndex = sceGxmProgramParameterGetResourceIndex(positionParam);

				//color param
				vertexArrtibs[1].streamIndex = 0;
				vertexArrtibs[1].offset = 12;
				vertexArrtibs[1].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[1].componentCount = 3;
				vertexArrtibs[1].regIndex = sceGxmProgramParameterGetResourceIndex(colorParam);

				vertexArrtibs[2].streamIndex = 0;
				vertexArrtibs[2].offset = 24;
				vertexArrtibs[2].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[2].componentCount = 2;
				vertexArrtibs[2].regIndex = sceGxmProgramParameterGetResourceIndex(textureParam);


				vertexstream[0].stride = sizeof(TextureNormalVertex);
				vertexstream[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;
			}
				break;
			case Andromeda::Graphics::TextureColor:
			{
				paramsCount = 3;

				vertexArrtibs = new SceGxmVertexAttribute[paramsCount];
				vertexstream = new SceGxmVertexStream[1];

				//get attribute index
				const SceGxmProgramParameter *positionParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iPosition");
				const SceGxmProgramParameter *colorParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iColor");
				const SceGxmProgramParameter *textureParam = sceGxmProgramFindParameterByName(_gxmVertexProgram, "iTexCoord");

				//position param
				vertexArrtibs[0].streamIndex = 0;
				vertexArrtibs[0].offset = 0;
				vertexArrtibs[0].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[0].componentCount = 3;
				vertexArrtibs[0].regIndex = sceGxmProgramParameterGetResourceIndex(positionParam);

				//color param
				vertexArrtibs[1].streamIndex = 0;
				vertexArrtibs[1].offset = 12;
				vertexArrtibs[1].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[1].componentCount = 3;
				vertexArrtibs[1].regIndex = sceGxmProgramParameterGetResourceIndex(colorParam);

				vertexArrtibs[2].streamIndex = 0;
				vertexArrtibs[2].offset = 24;
				vertexArrtibs[2].format = SCE_GXM_ATTRIBUTE_FORMAT_F32;
				vertexArrtibs[2].componentCount = 2;
				vertexArrtibs[2].regIndex = sceGxmProgramParameterGetResourceIndex(textureParam);


				vertexstream[0].stride = sizeof(TextureColorVertex);
				vertexstream[0].indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;
			}
				break;
			case Andromeda::Graphics::ColorNormal:
			{

			}
				break;
			case Andromeda::Graphics::TextureColorNormal:
			{

			}
				break;
			default:
				break;
			}

			SceGxmBlendInfo	blendInfo;
			blendInfo.colorFunc = SCE_GXM_BLEND_FUNC_ADD;
			blendInfo.alphaFunc = SCE_GXM_BLEND_FUNC_ADD;
			blendInfo.colorSrc = SCE_GXM_BLEND_FACTOR_SRC_ALPHA;
			blendInfo.colorDst = SCE_GXM_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			blendInfo.alphaSrc = SCE_GXM_BLEND_FACTOR_SRC_ALPHA;
			blendInfo.alphaDst = SCE_GXM_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			blendInfo.colorMask = SCE_GXM_COLOR_MASK_ALL;


			// create clear programs
			sceGxmShaderPatcherCreateVertexProgram(
				_shaderPatcher,
				_vertexProgramId,
				vertexArrtibs,
				paramsCount,
				vertexstream,
				1,
				&_vertexProgram);

			sceGxmShaderPatcherCreateFragmentProgram(
				_shaderPatcher,
				_fragmentProgramId,
				SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,
				SCE_GXM_MULTISAMPLE_NONE,
				&blendInfo,
				_gxmVertexProgram,
				&_fragmentProgram);
		}

		void ShaderGxm::SetShaderPatcher(SceGxmShaderPatcher* shaderPatcher)
		{
			_shaderPatcher = shaderPatcher;
		}

		void ShaderGxm::SetGxmContext(SceGxmContext* gxmContext)
		{
			_gxmContext = gxmContext;
		}

		void ShaderGxm::Bind()
		{
			sceGxmSetVertexProgram(_gxmContext, _vertexProgram);
			sceGxmSetFragmentProgram(_gxmContext, _fragmentProgram);
		}		

		void ShaderGxm::SetUniform(ShaderType shaderType, std::string name, int val)
		{

		}

		void ShaderGxm::SetUniform(ShaderType shaderType, std::string name, float val)
		{
			void *uniform_buffer;
			const SceGxmProgramParameter* param;

			if (shaderType == FragmentShader)
			{
				param = GetUniform(_fragmentProgramId, name);
				sceGxmReserveFragmentDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}
			else
			{
				param = GetUniform(_vertexProgramId, name);
				sceGxmReserveVertexDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}

			sceGxmSetUniformDataF(uniform_buffer, param, 0, 1, &val);
		}

		void ShaderGxm::SetUniform(ShaderType shaderType, std::string name, glm::vec3& val)
		{
			void *uniform_buffer;
			const SceGxmProgramParameter* param;

			if (shaderType == FragmentShader)
			{
				param = GetUniform(_fragmentProgramId, name);
				sceGxmReserveFragmentDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}
			else
			{
				param = GetUniform(_vertexProgramId, name);
				sceGxmReserveVertexDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}

			sceGxmSetUniformDataF(uniform_buffer, param, 0, 3, glm::value_ptr(val));
		}

		void ShaderGxm::SetUniform(ShaderType shaderType, std::string name, glm::vec4& val)
		{
			void *uniform_buffer;
			const SceGxmProgramParameter* param;

			if (shaderType == FragmentShader)
			{
				param = GetUniform(_fragmentProgramId, name);
				sceGxmReserveFragmentDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}
			else
			{
				param = GetUniform(_vertexProgramId, name);
				sceGxmReserveVertexDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}

			sceGxmSetUniformDataF(uniform_buffer, param, 0, 4, glm::value_ptr(val));
		}

		void ShaderGxm::SetUniform(ShaderType shaderType, std::string name, glm::mat3& val)
		{
			void *uniform_buffer;
			const SceGxmProgramParameter* param;

			if (shaderType == FragmentShader)
			{
				param = GetUniform(_fragmentProgramId, name);
				sceGxmReserveFragmentDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}
			else
			{
				param = GetUniform(_vertexProgramId, name);
				sceGxmReserveVertexDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}

			sceGxmSetUniformDataF(uniform_buffer, param, 0, 9, glm::value_ptr(val));
		}

		void ShaderGxm::SetUniform(ShaderType shaderType, std::string name, glm::mat4& val)
		{
			void *uniform_buffer;
			const SceGxmProgramParameter* param;

			if (shaderType == FragmentShader)
			{
				param = GetUniform(_fragmentProgramId, name);
				sceGxmReserveFragmentDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}
			else
			{
				param = GetUniform(_vertexProgramId, name);
				sceGxmReserveVertexDefaultUniformBuffer(_gxmContext, &uniform_buffer);
			}

			sceGxmSetUniformDataF(uniform_buffer, param, 0, 16, glm::value_ptr(val));
		}

		const SceGxmProgramParameter * ShaderGxm::GetUniform(SceGxmShaderPatcherId programId, std::string paramName)
		{
			const SceGxmProgram			*program;
			const SceGxmProgramParameter	*param;
			int		ret;

			program = sceGxmShaderPatcherGetProgramFromId(programId);

			param = sceGxmProgramFindParameterByName(program, paramName.c_str());
			if (!param)
			{
				Utils::Logger::Instance()->Log("Error: GetUniform - no param %s\n", paramName.c_str());
				return 0;
			}

			ret = sceGxmProgramParameterGetCategory(param);
			if (ret != SCE_GXM_PARAMETER_CATEGORY_UNIFORM)
			{
				Utils::Logger::Instance()->Log("Error: GetUniform - wrong category %s\n", paramName.c_str());
				return 0;
			}				

			return param;
		}
	}
}

