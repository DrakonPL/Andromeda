#include <Andromeda/Graphics/Models/ModelObj.h>
#include <Andromeda/FileSystem/FileManager.h>

namespace Andromeda
{
	namespace Graphics
	{
		ModelObj::ModelObj()
		{
			//default translations
			_position = glm::vec3(0.0f, 0.0f, 0.0f);
			_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			_scale = glm::vec3(1.0f, 1.0f, 1.0f);

			//color
			_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			_shader = 0;
		}

		ModelObj::~ModelObj()
		{
			//delete all materials
			for (size_t i = 0; i < _materials.size(); i++)
			{
				if (_materials[i]->Image != 0)
				{
  					TextureManager::Instance()->Remove(_materials[i]->Image);
				}

				delete _materials[i];
			}

			//delete all meshaes
			for (size_t i = 0; i < _meshes.size(); i++)
			{
				delete _meshes[i]->Mesh;
				delete _meshes[i];
			}

			_materials.clear();
			_meshes.clear();
		}

		std::string ModelObj::GetFolderFromPath(std::string& fileName)
		{
			size_t found;
			found = fileName.find_last_of("/\\");
			return fileName.substr(0, found) + "/";
		}
		
		std::string ModelObj::GetFileFromPath(std::string& fileName)
		{
			size_t found;
			found = fileName.find_last_of("/\\");
			return fileName.substr(found + 1);
		}


		void ModelObj::LoadModel(std::vector<tinyobj::shape_t> &shapes, std::vector<tinyobj::material_t> &materials, std::string location)
		{
			//load all meterials
			for (size_t i = 0; i < materials.size(); i++)
			{
				ModelMaterial* material = new ModelMaterial();

				//material name
				material->Name = materials[i].name;
				
				//material colors
				material->SetColor(MaterialColorType::MaterialColorAmbient, glm::vec3(materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]));
				material->SetColor(MaterialColorType::MaterialColorDiffuse, glm::vec3(materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]));
				material->SetColor(MaterialColorType::MaterialColorSpecular, glm::vec3(materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]));

				//material textures
				if (materials[i].diffuse_texname != "")
				{
					material->SetTextureName(MaterialTextureType::MaterialTextureDiffuse, location + materials[i].diffuse_texname);
					material->Image = TextureManager::Instance()->LoadFromFile(location + materials[i].diffuse_texname);
				}

				if (materials[i].specular_texname != "")
				{
					material->SetTextureName(MaterialTextureType::MaterialTextureSpecular, location + materials[i].specular_texname);
				}

				if (materials[i].bump_texname != "")
				{
					material->SetTextureName(MaterialTextureType::MaterialTextureBump, location + materials[i].bump_texname);
				}

				_materials.push_back(material);
			}

			//ctreate all shapes
			for (size_t i = 0; i < shapes.size(); i++)
			{
				VertexArrayObject* mesh;
				
				if (shapes[i].mesh.normals.size() > 0)
				{
					mesh = RenderManager::Instance()->CreateVertexArrayObject(TextureNormal, StaticDraw);
				}
				else
				{
					mesh = RenderManager::Instance()->CreateVertexArrayObject(TextureColor, StaticDraw);
				}			
				

				//create vertices
				mesh->CreateVertices(shapes[i].mesh.positions.size() / 3);

				//get vertices
				TextureColorVertex* _simpleData = static_cast<TextureColorVertex*>(mesh->GetVertices());

				for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++)
				{
					_simpleData[v].x = shapes[i].mesh.positions[3 * v + 0];
					_simpleData[v].y = shapes[i].mesh.positions[3 * v + 1];
					_simpleData[v].z = shapes[i].mesh.positions[3 * v + 2];

					_simpleData[v].u = shapes[i].mesh.texcoords[2 * v + 0];
					_simpleData[v].v = shapes[i].mesh.texcoords[2 * v + 1];

					if (_simpleData[v].v < 0.0f)
					{
						_simpleData[v].v += 1.0f;
					}

					if (_simpleData[v].v > 1.0f)
					{
						_simpleData[v].v -= 1.0f;
					}

					_simpleData[v].v = 1.0f - _simpleData[v].v;

					//TODO test hack
					if (shapes[i].mesh.normals.size() > 0)
					{
						TextureNormalVertex* textureNormalData = static_cast<TextureNormalVertex*>(mesh->GetVertices());

						textureNormalData[v].nx = shapes[i].mesh.normals[3 * v + 0];
						textureNormalData[v].ny = shapes[i].mesh.normals[3 * v + 1];
						textureNormalData[v].nz = shapes[i].mesh.normals[3 * v + 2];
					}
					else
					{
						_simpleData[v].r = 1.0f;	_simpleData[v].g = 1.0f;	_simpleData[v].b = 1.0f;
					}					
				}

				//create indices
				mesh->CreateIndices(shapes[i].mesh.indices.size());

				//get indices
				unsigned short* _indices = static_cast<unsigned short*>(mesh->GetIndices());

				//set data
				for (unsigned int in = 0; in < shapes[i].mesh.indices.size(); in++)
				{
					_indices[in] = shapes[i].mesh.indices[in];
				}

				//generate buffer object
				mesh->Generate();

				ModelMesh* modelMesh = new ModelMesh();

				modelMesh->Name = shapes[i].name;
				modelMesh->MaterialId = shapes[i].mesh.material_ids[0];
				modelMesh->Mesh = mesh;

				if (modelMesh->MaterialId < 0)
					modelMesh->MaterialId = 0;

				//add to collection
				_meshes.push_back(modelMesh);
			}
		}

		bool ModelObj::LoadModel(std::string fileName)
		{
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			std::string err;

			_location = GetFolderFromPath(fileName);

			bool ret = tinyobj::LoadObj(shapes, materials, err, fileName.c_str(), _location.c_str());

			if (!err.empty())
			{
				return false;
			}

			LoadModel(shapes, materials, _location);

			return true;
		}

		void ModelObj::ConvertToBinary(std::string fileName, std::string saveFile)
		{
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			std::string err;

			_location = GetFolderFromPath(fileName);

			bool ret = tinyobj::LoadObj(shapes, materials, err, fileName.c_str(), _location.c_str());

			if (!err.empty())
			{
				return;
			}

			//create file to write
			FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(saveFile);

			if (file == 0)
			{
				return;
			}

			file->Open(FileSystem::Write, FileSystem::Binary);

			//mesh count 
			uint32_t nMeshes = static_cast<uint32_t>(shapes.size());
			file->Write(&nMeshes, sizeof(uint32_t), 1);

			//materials count 
			uint32_t materialsCount = static_cast<uint32_t>(materials.size());
			file->Write(&materialsCount, sizeof(uint32_t), 1);

			//write all meshes
			for (size_t i = 0; i < shapes.size(); i++)
			{
				//name
				uint32_t nameLength = (uint32_t)shapes[i].name.length();
				file->Write(&nameLength, sizeof(uint32_t), 1);
				file->Write(&shapes[i].name[0], sizeof(char), strlen(shapes[i].name.c_str()));

				//data
				uint32_t nVertices = (uint32_t)shapes[i].mesh.positions.size();
				uint32_t nNormals = (uint32_t)shapes[i].mesh.normals.size();
				uint32_t nTexcoords = (uint32_t)shapes[i].mesh.texcoords.size();
				uint32_t nMaterials = (uint32_t)shapes[i].mesh.material_ids.size();
				uint32_t nIndices = (uint32_t)shapes[i].mesh.indices.size();

				file->Write(&nVertices, sizeof(uint32_t), 1);
				file->Write(&nNormals, sizeof(uint32_t), 1);
				file->Write(&nTexcoords, sizeof(uint32_t), 1);
				file->Write(&nMaterials, sizeof(uint32_t), 1);
				file->Write(&nIndices, sizeof(uint32_t), 1);

				file->Write(&shapes[i].mesh.positions[0], sizeof(float), nVertices);
				file->Write(&shapes[i].mesh.normals[0], sizeof(float), nNormals);
				file->Write(&shapes[i].mesh.texcoords[0], sizeof(float), nTexcoords);
				file->Write(&shapes[i].mesh.material_ids[0], sizeof(int), nMaterials);
				file->Write(&shapes[i].mesh.indices[0], sizeof(unsigned int), nIndices);
			}

			//write all meterials
			for (size_t i = 0; i < materialsCount; i++)
			{
				//name
				uint32_t nameLength = (uint32_t)materials[i].name.length();
				file->Write(&nameLength, sizeof(uint32_t), 1);
				file->Write(&materials[i].name[0], sizeof(char), strlen(materials[i].name.c_str()));

				//difuse texture just now
				nameLength = (uint32_t)materials[i].diffuse_texname.length();
				file->Write(&nameLength, sizeof(uint32_t), 1);
				file->Write(&materials[i].diffuse_texname[0], sizeof(char), strlen(materials[i].diffuse_texname.c_str()));
			}

			file->Close();
		}

		void ModelObj::LoadBinary(std::string fileName)
		{
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			//create file to write
			FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(fileName);

			if (file == 0)
			{
				return;
			}

			file->Open(FileSystem::Read, FileSystem::Binary);

			//mesh count 
			uint32_t nMeshes;
			file->Read(&nMeshes, sizeof(uint32_t), 1);

			//materials count 
			uint32_t materialsCount;
			file->Read(&materialsCount, sizeof(uint32_t), 1);

			shapes.resize(nMeshes);
			materials.resize(materialsCount);

			for (size_t i = 0; i < nMeshes; i++)
			{
				uint32_t nVertices = 0, nNormals = 0, nTexcoords = 0, nMaterials = 0, nIndices = 0;

				uint32_t nameLength;
				file->Read(&nameLength, sizeof(uint32_t), 1);
				shapes[i].name.resize(nameLength);

				file->Read(&shapes[i].name[0], sizeof(char), nameLength);

				file->Read(&nVertices, sizeof(uint32_t), 1);
				file->Read(&nNormals, sizeof(uint32_t), 1);
				file->Read(&nTexcoords, sizeof(uint32_t), 1);
				file->Read(&nMaterials, sizeof(uint32_t), 1);
				file->Read(&nIndices, sizeof(uint32_t), 1);

				shapes[i].mesh.positions.resize(nVertices);
				shapes[i].mesh.normals.resize(nNormals);
				shapes[i].mesh.texcoords.resize(nTexcoords);
				shapes[i].mesh.material_ids.resize(nTexcoords);
				shapes[i].mesh.indices.resize(nIndices);

				file->Read(&shapes[i].mesh.positions[0], sizeof(float), nVertices);
				file->Read(&shapes[i].mesh.normals[0], sizeof(float), nNormals);
				file->Read(&shapes[i].mesh.texcoords[0], sizeof(float), nTexcoords);
				file->Read(&shapes[i].mesh.material_ids[0], sizeof(int), nMaterials);
				file->Read(&shapes[i].mesh.indices[0], sizeof(unsigned int), nIndices);
			}

			//read all meterials
			for (size_t i = 0; i < materialsCount; i++)
			{
				//material name
				uint32_t nameLength;
				file->Read(&nameLength, sizeof(uint32_t), 1);

				materials[i].name.resize(nameLength);
				file->Read(&materials[i].name[0], sizeof(char), nameLength);

				//difuse texture just now
				file->Read(&nameLength, sizeof(uint32_t), 1);

				materials[i].diffuse_texname.resize(nameLength);
				file->Read(&materials[i].diffuse_texname[0], sizeof(char), nameLength);
			}

			file->Close();
			delete file;

			_location = GetFolderFromPath(fileName);

			LoadModel(shapes, materials, _location);
		}

		void ModelObj::SetShader(Shader* shader)
		{
			_shader = shader;
		}

		void ModelObj::SetPosition(glm::vec3 position)
		{
			_position = position;
		}

		void ModelObj::SetRotationn(glm::vec3 rotation)
		{
			_rotation = rotation;
		}

		void ModelObj::SetScale(glm::vec3 scale)
		{
			_scale = scale;
		}

		Shader* ModelObj::GetShader()
		{
			return _shader;
		}

		glm::vec3 ModelObj::GetPosition()
		{
			return _position;
		}

		glm::vec3 ModelObj::GetRotation()
		{
			return _rotation;
		}

		glm::vec3 ModelObj::GetScale()
		{
			return _scale;
		}

		glm::mat4 ModelObj::GetModelMatrix()
		{
			_modelMatrix = glm::mat4();

			//translation
			_modelMatrix = glm::translate(_modelMatrix, _position);

			//rotate
			_modelMatrix = glm::rotate(_modelMatrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			_modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			_modelMatrix = glm::rotate(_modelMatrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			//scale
			_modelMatrix = glm::scale(_modelMatrix, _scale);

			return _modelMatrix;
		}

		void ModelObj::SetColor(glm::vec4 color)
		{
			_color = color;
		}

		glm::vec4 ModelObj::GetColor()
		{
			return _color;
		}

		void ModelObj::Draw()
		{
			for (size_t i = 0; i < _meshes.size(); i++)
			{
				ModelMesh* mesh = _meshes[i];
				ModelMaterial* material = _materials[mesh->MaterialId];

				//use texture
				if (material->GetTextureName(MaterialTextureType::MaterialTextureDiffuse) != "")
				{
					RenderManager::Instance()->UseTexture(material->Image);
				}				

				//render
				_meshes[i]->Mesh->Draw();
			}
		}
	}
}