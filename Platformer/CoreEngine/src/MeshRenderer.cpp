#include "stdafx.h"

#include <MeshRenderer.h>
#include <ResourceManager.h>

using namespace CoreEngineNS;

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Awake()
{

}

void MeshRenderer::Update()
{

}

void MeshRenderer::Draw()
{

}

void MeshRenderer::SetMesh(Model* p_model)
{
	m_model = p_model;
}

 Model* MeshRenderer::GetMesh()
{
	return m_model;
}
