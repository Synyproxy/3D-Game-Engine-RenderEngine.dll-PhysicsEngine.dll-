#include "stdafx.h"

#include <ResourceManager.h>

using namespace CoreEngineNS;

ResourceManager::ResourceManager(): m_modelsRootDir {"res/meshes/"}, m_shaderRootDir {"res/shaders"}
{
}

ResourceManager::~ResourceManager()
{
}
