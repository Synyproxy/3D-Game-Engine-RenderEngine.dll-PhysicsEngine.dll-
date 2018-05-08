#include "stdafx.h"

#include <Collider.h>
#include <GameObject.h>
#include <Transform.h>

using namespace CoreEngineNS;

Collider::Collider()
{
	m_sphere = new Sphere();
}

Collider::~Collider()
{
}

Primitive* Collider::GetCollider()
{
	return m_sphere;
}


void Collider::Update()
{
	m_sphere->Position() = m_parent->GetComponent<Transform>().GetPosition();
}
