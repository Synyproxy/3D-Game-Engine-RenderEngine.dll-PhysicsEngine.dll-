#pragma once

#include <math/Vec2.h>
#include <Component.h>

namespace CoreEngineNS
{
	class Transform : public Component
	{
	private:
		Vec2 m_position;

	public:
		Transform();
		~Transform();

		void Awake() override;
		void Update() override;
		void Draw() override;

		const Vec2& GetPosition() const;
		void SetPosition(const Vec2& p_position);
	};

}