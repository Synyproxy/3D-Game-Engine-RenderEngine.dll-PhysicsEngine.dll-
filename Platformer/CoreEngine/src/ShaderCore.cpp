#include  "stdafx.h"

#include <ShaderCore.h>

using namespace CoreEngineNS;

ShaderCore::ShaderCore()
{
}

ShaderCore::~ShaderCore()
{
}
//
//void ShaderCore::Awake()
//{
//
//}
//
//void ShaderCore::Update()
//{
//
//}
//
//void ShaderCore::Draw()
//{
//
//}

void ShaderCore::SetShader(Shader* p_shader)
{
	m_shader = p_shader;
}

Shader* ShaderCore::GetShader()
{
	return  m_shader;
}
