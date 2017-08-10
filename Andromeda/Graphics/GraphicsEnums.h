#ifndef GraphicsEnums_H
#define GraphicsEnums_H

namespace Andromeda
{
	namespace Graphics
	{
		enum VertexType
		{
			Simple,
			Color,
			Textured,
			TextureNormal,
			TextureColor,
			ColorNormal,
			TextureColorNormal,
			SpriteType
		};

		enum VertexPrimitive
		{
			Triangle,
			TriangleStrip,
			TriangleFan,
			Lines
		};

		enum MatrixType
		{
			ViewMatrix,
			ProjectionMatrix,
			ModelMatrix
		};

		enum ShaderType
		{
			VertexShader,
			FragmentShader
		};

		enum TextureFilerType
		{
			NearestFilter,
			LinearFilter
		};

		enum VertexBufferDrawType
		{
			StaticDraw,
			DynamicDraw
		};

		enum TextureFontAlign
		{
			FontLeft,
			FontCenter,
			FontRight
		};

		enum TextureColorType
		{
			Texture_RGBA,
			Texture_RGB,
			Texture_YVU420P2
		};

		enum MaterialColorType
		{
			MaterialColorAmbient,
			MaterialColorDiffuse,
			MaterialColorSpecular
		};

		enum MaterialTextureType
		{
			MaterialTextureDiffuse,
			MaterialTextureSpecular,
			MaterialTextureBump
		};
	}
}

#endif
