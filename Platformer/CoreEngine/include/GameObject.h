#pragma once

#include "stdafx.h"
#include <Component.h>

namespace CoreEngineNS
{
	class Component;
	class GameObject;

	class GameObject
	{
	protected:
		bool m_active = true;
		std::vector<std::unique_ptr<Component>> m_components;

		ComponentArray m_componentArray;
		ComponentBitSet m_componentBitSet;

	public:

		~GameObject() {}

		void Update()
		{
			for (auto& c : m_components) c->Update();
		}

		void Draw()
		{
			for (auto& c : m_components) c->Draw();
		}

		bool IsActive() const { return m_active; }
		void Destroy() { m_active = false; }

		template<typename T>
		bool HasComponent() const
		{
			return m_componentBitSet[getComponentTypeID<T>()];
		}

		template<typename T, typename ...TArgs>
		T& AddComponent(TArgs&&... mArgs)
		{
			//Core::Debug::Assertion::Assert(!HasComponent <T>(), "ERROR::ENTITY_HAS_ALREADY::COMPONENT");

			T* c(new T(std::forward<TArgs>(mArgs)...));

			c->m_parent = this;
			std::unique_ptr<Component> cPtr{ c };
			m_components.emplace_back(std::move(cPtr));

			m_componentArray[getComponentTypeID<T>()] = c;
			m_componentBitSet[getComponentTypeID<T>()] = true;

			c->Awake();
			return *c;
		}

		template<typename T> T& GetComponent() const
		{
			auto ptr(m_componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}
	};
}
