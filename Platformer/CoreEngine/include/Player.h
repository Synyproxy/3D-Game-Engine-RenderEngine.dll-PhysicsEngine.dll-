#pragma once

#include <GameObject.h>
#include <Transform.h>

namespace CoreEngineNS
{
	class Player : public GameObject
	{
	private:
		Transform* transform;
		float m_movementSpeed;

	public:
		~Player();

		void Awake() override;
		void Update() override;
	};
}