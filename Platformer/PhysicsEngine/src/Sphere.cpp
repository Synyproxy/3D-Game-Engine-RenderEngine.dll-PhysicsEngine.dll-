#include "stdafx.h"

#include <Sphere.h>

using namespace PhysicsEngineNS;

Sphere::Sphere(const glm::vec3 p_position, const float& p_radious): m_radius{ p_radious }
{
	m_position = p_position;
	m_type = EPrimitiveType::SPHERE_TYPE;
}

Sphere::~Sphere()
{
}

float Sphere::Radius()
{
	return m_radius;
}
