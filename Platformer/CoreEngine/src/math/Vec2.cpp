#include "stdafx.h"

#include <math/Vec2.h>

using namespace CoreEngineNS;

Vec2::Vec2(float p_x, float p_y)
	: m_x {p_x}, m_y {p_y}
{
}

Vec2::~Vec2()
{
}

Vec2::Vec2(const Vec2 & other)
{
	m_x = other.X();
	m_y = other.Y();
}

float Vec2::X() const
{
	return m_x;
}

float Vec2::Y() const
{
	return m_y;
}

void Vec2::X(float p_x)
{
	m_x = p_x;
}

void Vec2::Y(float p_y)
{
	m_y = p_y;
}

bool Vec2::operator==(const Vec2& other) const
{
	return (m_x == other.X() && m_y == other.Y());
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(m_x + other.X(), m_y + other.Y());
}

float Vec2::Magnitude()
{
	return sqrt((m_x * m_x) + (m_y * m_y));
}

Vec2 Vec2::Normalize()
{
	float magnitude = Magnitude();

	if (magnitude != 0)
	{
		m_x /= magnitude;
		m_y /= magnitude;
	}

	return *this;
}

