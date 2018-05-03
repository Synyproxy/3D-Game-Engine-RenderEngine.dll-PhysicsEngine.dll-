#pragma once

#include "CoreEngineAPI.h"
#include "RenderEngine.h"


using namespace RenderEngineNS;

namespace CoreEngineNS
{
	class COREENGINE_API CoreEngine
	{
	private:
		RenderEngine* m_renderEngine;

	public:
		CoreEngine();
		~CoreEngine();
		void IgniteRenderEngine(const int& p_width, const int& p_height);
		void Run();
	};
}