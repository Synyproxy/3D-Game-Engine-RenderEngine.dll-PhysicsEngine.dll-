// RenderEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "RenderEngine.h"


RenderEngineNS::RenderEngine::RenderEngine()
{
	std::cout << "RenderEngine On" << std::endl;
}

RenderEngineNS::RenderEngine::~RenderEngine()
{
	std::cout << "RenderEngine Off" << std::endl;
}
