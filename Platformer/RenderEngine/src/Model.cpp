#include "stdafx.h"

#include <Model.h>

using namespace RenderEngineNS;

Model::Model(std::string& p_path)
{
	LoadModel(p_path);
}

Model::~Model()
{

}

void Model::LoadModel(std::string & p_path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(p_path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		//Log::Logger(importer.GetErrorString(), LogLevel::FILE);
		return;
	}

	m_directory = p_path.substr(0, p_path.find_last_of('/'));


	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* p_node, const aiScene* p_scene)
{
	for (GLuint i = 0; i < p_node->mNumMeshes; i++)
	{
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];

		m_meshes.push_back(this->ProcessMesh(mesh, p_scene));
	}

	for (GLuint i = 0; i < p_node->mNumChildren; i++)
	{
		ProcessNode(p_node->mChildren[i], p_scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* p_mesh, const aiScene* p_scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (GLuint i = 0; i < p_mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		// Positions
		vector.x = p_mesh->mVertices[i].x;
		vector.y = p_mesh->mVertices[i].y;
		vector.z = p_mesh->mVertices[i].z;
		vertex.Position = vector;

		// Normals
		vector.x = p_mesh->mNormals[i].x;
		vector.y = p_mesh->mNormals[i].y;
		vector.z = p_mesh->mNormals[i].z;
		vertex.Normal = vector;

		// Texture Coordinates
		if (p_mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = p_mesh->mTextureCoords[0][i].x;
			vec.y = p_mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < p_mesh->mNumFaces; i++)
	{
		aiFace face = p_mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// Process materials
	if (p_mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = p_scene->mMaterials[p_mesh->mMaterialIndex];

		//Diffuse maps
		std::vector<Texture> diffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		//Specular maps
		std::vector<Texture> specularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		//Normal maps
		std::vector<Texture> normalMaps = this->LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* p_material, aiTextureType p_type, std::string p_typeName)
{
	std::vector<Texture> textures;

	for (GLuint i = 0; i < p_material->GetTextureCount(p_type); i++)
	{
		aiString str;
		p_material->GetTexture(p_type, i, &str);

		GLboolean skip = false;

		for (GLuint j = 0; j < m_loadedTextures.size(); j++)
		{
			if (m_loadedTextures[j].m_path == str)
			{
				textures.push_back(m_loadedTextures[j]);
				skip = true;

				break;
			}
		}

		if (!skip)
		{   // If texture hasn't been loaded already, load it
			Texture texture;
			texture.m_id = TextureFromFile(str.C_Str(), this->m_directory);
			texture.m_type = p_typeName;
			texture.m_path = str;
			textures.push_back(texture);

			this->m_loadedTextures.push_back(texture);
		}
	}

	return textures;
}

GLint Model::TextureFromFile(const char* p_path, std::string p_directory)
{
	//Generate texture ID and load texture data
	std::string filename = std::string(p_path);
	filename = p_directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;

	unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return textureID;
}

void Model::SetShader(Shader* p_shader)
{
	m_shader = p_shader;
}