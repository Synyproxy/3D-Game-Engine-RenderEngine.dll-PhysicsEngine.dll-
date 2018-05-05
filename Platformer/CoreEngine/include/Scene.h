#pragma once

#include "stdafx.h"
#include <GameObject.h>
#include <Player.h>

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

		template<typename  T>
		GameObject& AddGameObject()
		{
			T* e = new T();
			std::unique_ptr<GameObject> ePtr{ e };

			ePtr->AddComponent<Transform>();
			m_gameObjects.emplace_back(std::move(ePtr));
			return *e;
		}

		//TODO
		//GameObject& Cube();

		Player* AddPlayer();


		int Count();
	};
}