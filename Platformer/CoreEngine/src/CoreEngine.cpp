// CoreEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "CoreEngine.h"

using namespace CoreEngineNS;

CoreEngine::CoreEngine(): m_renderEngine(nullptr)
{
	std::cout << "CoreEngine On" << std::endl;
}

CoreEngine::~CoreEngine()
{
	std::cout << "CoreEngine Off" << std::endl;
	if (m_renderEngine != nullptr)
		delete(m_renderEngine);
}

void CoreEngine::IgniteRenderEngine(const int& p_width, const int& p_height)
{
	m_renderEngine = new RenderEngine();

	m_renderEngine->SetupWindow(p_width, p_height);
}

void CoreEngine::Run()
{
	m_renderEngine->Update();
}
