#include "stdafx.h"

#include <ResourceManager.h>

using namespace CoreEngineNS;

ResourceManager& ResourceManager::Instance()
{
	static ResourceManager instance;
	return instance;
}


ResourceManager::ResourceManager() : m_modelsRootDir {"res/meshes/"}, m_shaderRootDir {"res/shaders/"}
{
}

void ResourceManager::FreeResources()
{

	//m_modelResources.clear();
	//m_shaderResources.clear();

	for (auto& modelPair : m_modelResources)
		delete modelPair.second;


	for (auto& shaderPair : m_shaderResources)
		delete shaderPair.second;

	std::cout << "Called" << std::endl;;
}

Model* ResourceManager::LoadModel(const std::string && p_name, const std::string && p_file, bool p_forceReload)
{
	if (!p_forceReload && m_modelResources.find(p_name) != m_modelResources.end())
		return m_modelResources[p_name];

	/*Model* model = new Model(m_modelsRootDir + p_file);
	m_modelResources.emplace(p_name, model);
	return model;*/
	auto res = m_modelResources.emplace(p_name, new Model(m_modelsRootDir + p_file));
	return res.first->second;
}

Shader* ResourceManager::LoadShader(const std::string&& p_name, const std::string&& p_vertShader, const std::string&& p_fragShader, bool p_forceReload)
{
	if (!p_forceReload && m_shaderResources.find(p_name) != m_shaderResources.end())
		return m_shaderResources[p_name];

	auto res = m_shaderResources.emplace(p_name, new Shader(m_shaderRootDir + p_vertShader, m_shaderRootDir + p_fragShader));
	return res.first->second;
}