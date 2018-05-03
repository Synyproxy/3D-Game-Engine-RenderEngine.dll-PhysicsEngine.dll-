#pragma once

#include "RenderEngineAPI.h"
#include <Window.h>

namespace RenderEngineNS
{
	class RENDERENGINE_API RenderEngine
	{
	private:
		std::shared_ptr<Window> m_window;
		bool m_isRunning;
		int m_width;
		int m_height;
	

	public:
		RenderEngine();
		~RenderEngine();

		void SetupWindow(const int& p_width, const int& p_height);
		void Update();

		bool IsRunning();

		std::shared_ptr<Window> GetWindow();
		int WindowWidth() const;
		int WindowHeight() const;
	};
}