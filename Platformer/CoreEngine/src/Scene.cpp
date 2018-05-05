#include "stdafx.h"

#include <Scene.h>
#include <Transform.h>

using namespace CoreEngineNS;

Scene::Scene()
{

}
Scene::~Scene()
{

}

const std::vector<std::shared_ptr<GameObject>>& Scene::Hierarchy()
{
	return m_gameObjects;
}

//TODO Make this Template and Make sure T derives from GameObject
GameObject& Scene::AddEntity()
{
	GameObject* e = new GameObject();
	std::unique_ptr<GameObject> ePtr{ e };

	e->AddComponent<Transform>();
	m_gameObjects.emplace_back(std::move(ePtr));
	return *e;
}


Player* Scene::AddPlayer()
{
	Player* e = new Player();
	std::unique_ptr<GameObject> ePtr{ e };
	e->AddComponent<Transform>();
	m_gameObjects.emplace_back(std::move(ePtr));
	return e;
}

int Scene::Count()
{
	return m_gameObjects.size();
}
