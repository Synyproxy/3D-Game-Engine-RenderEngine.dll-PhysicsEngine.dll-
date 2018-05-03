#pragma once

namespace CoreEngineNS
{
	class Vec2
	{
	private:
		float m_x;
		float m_y;

	public:
		Vec2(float p_x = 0, float p_y = 0);
		~Vec2();
		Vec2(const Vec2& other);

		//Getters / Setters
		float X() const;
		float Y() const;
		void X(float p_x);
		void Y(float p_y);

		bool operator==(const Vec2& other) const;
		Vec2 operator+(const Vec2& other) const;

		float Magnitude();
		Vec2 Normalize();

	};
}