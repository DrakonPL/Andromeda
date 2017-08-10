#include <Andromeda/Graphics/GL/VertexArrayObjectGL3.h>
#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/VertexTypes.h>

#define GLEW_STATIC
#include <GL/glew.h>


namespace Andromeda
{
	namespace Graphics
	{
		VertexArrayObjectGL3::VertexArrayObjectGL3()
		{
			_vao = -1;
			_vbo = -1;
			_vbi = -1;

			_drawMode = GL_TRIANGLES;
		}

		VertexArrayObjectGL3::~VertexArrayObjectGL3()
		{
			if (_vao != -1)
			{
				glDeleteVertexArrays(1, &_vao);
				glDeleteBuffers(1, &_vbo);
				glDeleteBuffers(1, &_vbi);
			}
		}

		void VertexArrayObjectGL3::SetVertexPrimitive(VertexPrimitive vertexPrimitive)
		{
			_vertexPrimitive = vertexPrimitive;

			switch (vertexPrimitive)
			{
			case Triangle:
				_drawMode = GL_TRIANGLES;
				break;
			case TriangleFan:
				_drawMode = GL_TRIANGLE_FAN;
				break;
			case TriangleStrip:
				_drawMode = GL_TRIANGLE_STRIP;
				break;
			case Lines:
				_drawMode = GL_LINES;
				break;
			}
		}

		void VertexArrayObjectGL3::SetVertexType(VertexType vertexType)
		{
			_vertexType = vertexType;
			_vertexSize = RenderManager::Instance()->GetVertexSize(vertexType);
		}

		void VertexArrayObjectGL3::SetVertexBufferDrawType(VertexBufferDrawType drawType)
		{
			_vertexBufferDrawType = drawType;
		}

		void VertexArrayObjectGL3::CreateVertices(int count)
		{
			_verticesCount = count;
			_vertices = RenderManager::Instance()->CreateVertices(_vertexType, count);
		}

		void VertexArrayObjectGL3::SetVertices(void* data, int count)
		{
			_vertices = data;
			_verticesCount = count;
		}

		void VertexArrayObjectGL3::UpdateVertices(void* data, int count)
		{
			if (_vbo != -1)
			{
				glBindBuffer(GL_ARRAY_BUFFER, _vbo);
				glBufferSubData(GL_ARRAY_BUFFER, 0,_vertexSize * count, data);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				delete [] data;
			}
		}

		void* VertexArrayObjectGL3::GetVertices()
		{
			return _vertices;
		}

		void VertexArrayObjectGL3::CreateIndices(int count)
		{
			_indicesCount = count;
			_indices = new unsigned int[count];
		}

		void VertexArrayObjectGL3::SetIndicesNumber(int count)
		{
			_indicesCount = count;
		}

		void VertexArrayObjectGL3::SetIndices(void* data, int count)
		{
			_indices = data;
			_indicesCount = count;
		}

		void VertexArrayObjectGL3::UpdateIndices(void* data, int count)
		{
			if (_vbi != -1)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbi);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned short) * count, data);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

				delete[] data;
			}			
		}

		void* VertexArrayObjectGL3::GetIndices()
		{
			return _indices;
		}

		void VertexArrayObjectGL3::Generate()
		{
			//generate vertex buffer object
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);

			if (_vertexBufferDrawType == DynamicDraw)
			{
				glBufferData(GL_ARRAY_BUFFER, _vertexSize * _verticesCount, _vertices, GL_DYNAMIC_DRAW);
			}
			else if (_vertexBufferDrawType == StaticDraw)
			{
				glBufferData(GL_ARRAY_BUFFER, _vertexSize * _verticesCount, _vertices, GL_STATIC_DRAW);
			}
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			//it's safe to delete vertices info
			delete[] _vertices;

			//generate indices buffer
			glGenBuffers(1, &_vbi);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbi);

			if (_vertexBufferDrawType == DynamicDraw)
			{
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * _indicesCount, _indices, GL_DYNAMIC_DRAW);
			}
			else if (_vertexBufferDrawType == StaticDraw)
			{
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * _indicesCount, _indices, GL_STATIC_DRAW);
			}
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			//it's safe to delete indices info
			delete[] _indices;

			//generate vertex array object
			glGenVertexArrays(1, &_vao);
			glBindVertexArray(_vao);
			
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbi);

			//set basic atribute
			SetVertexArtibutes();

			glBindVertexArray(0);
		}

		void VertexArrayObjectGL3::SetVertexArtibutes()
		{
			switch(_vertexType)
			{
				case Simple:
				{
					//position attribute
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)0);
					glEnableVertexAttribArray(0);
				}
				break;
				case Color: 
				{
					//position attribute
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)0);
					glEnableVertexAttribArray(0);

					// Color attribute
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)(3 * sizeof(GLfloat)));
					glEnableVertexAttribArray(1);
				}
				break;
				case Textured:
				{
					//position attribute
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)0);
					glEnableVertexAttribArray(0);

					// TexCoord attribute
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)(3 * sizeof(GLfloat)));
					glEnableVertexAttribArray(1);
				}
				break;
				case TextureNormal:
				{
					//position attribute
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)0);
					glEnableVertexAttribArray(0);

					//normal attribute
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)(3 * sizeof(GLfloat)));
					glEnableVertexAttribArray(1);

					// TexCoord attribute
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)(6 * sizeof(GLfloat)));
					glEnableVertexAttribArray(2);

				}
				break;
				case TextureColor:
				{
					//position attribute
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)0);
					glEnableVertexAttribArray(0);

					// Color attribute
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)(3 * sizeof(GLfloat)));
					glEnableVertexAttribArray(1);

					// TexCoord attribute
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _vertexSize, (GLvoid*)(6 * sizeof(GLfloat)));
					glEnableVertexAttribArray(2);
				}
				break;
				case ColorNormal: break;
				case TextureColorNormal: break;
				default: break;
			}
		}

		void VertexArrayObjectGL3::Draw()
		{
			//bind buffer
			glBindVertexArray(_vao);

			//draw vertices
			glDrawElements(_drawMode, _indicesCount, GL_UNSIGNED_SHORT, 0);

			//unbind buffer
			glBindVertexArray(0);
		}
	}
}
