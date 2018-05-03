#pragma once

#include "stdafx.h"
#include <GameObject.h>

namespace CoreEngineNS
{
	class Scene
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;

	public:
		Scene();
		~Scene();

		const std::vector<std::shared_ptr<GameObject>>& Hierarchy();

		GameObject& AddEntity();
		//TODO
		//GameObject& Cube();

		int Count();
	};
}