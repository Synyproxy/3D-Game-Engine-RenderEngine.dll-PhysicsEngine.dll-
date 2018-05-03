#pragma once

#include "stdafx.h"
#include <Mesh.h>
#include <Shader.h>

namespace RenderEngineNS
{
	class Model
	{
	private:
		std::vector<Mesh> m_meshes;
		std::string m_directory;
		std::vector<Texture> m_loadedTextures;
		Shader* m_shader;

		void LoadModel(std::string& p_path);
		void ProcessNode(aiNode* p_node, const aiScene* p_scene);

		Mesh ProcessMesh(aiMesh* p_mesh, const aiScene *scene);

		std::vector<Texture> LoadMaterialTextures(aiMaterial* p_material, aiTextureType p_type, std::string p_typeName);
		GLint TextureFromFile(const char* p_path, std::string p_directory);
		void SetShader(Shader* p_shader);

	public:
		Model(std::string& p_path);
		~Model();


	};
}