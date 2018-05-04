#pragma once

#include <Shader.h>
#include <Model.h>

using namespace RenderEngineNS;

namespace CoreEngineNS
{
	using Model_ptr = std::unique_ptr<Model>;
	using Shader_ptr = std::unique_ptr<Shader>;

	class ResourceManager
	{
	private:
		std::string m_modelsRootDir;
		std::string m_shaderRootDir;

	public:
		ResourceManager();
		~ResourceManager();


	};
}