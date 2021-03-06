// PhysicsEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "PhysicsEngine.h"

using namespace PhysicsEngineNS;

Force Gravity(0.0f, -9.8f, 0.0f);

PhysicsEngine::PhysicsEngine()
{
	std::cout << "Physics Engine On" << std::endl;
}

PhysicsEngine::~PhysicsEngine()
{
	std::cout << "Physics Engine Off" << std::endl;
}

//bool PhysicsEngine::Intersect(Primitive& aPrimitive1, Primitive& aPrimitive2, CollisionInformation& aCollisionInfo)
//{
//	bool intersect = false;
//
//	if (aPrimitive1.Type() == EPrimitiveType::SPHERE_TYPE && aPrimitive2.Type() == EPrimitiveType::SPHERE_TYPE)
//	{
//		Sphere& sphere1 = static_cast<Sphere&>(aPrimitive1);
//		Sphere& sphere2 = static_cast<Sphere&>(aPrimitive2);
//
//		float distance = sqrt(pow(aPrimitive1.Position().x - aPrimitive2.Position().x, 2.0) + pow(aPrimitive1.Position().y - aPrimitive2.Position().y, 2.0) + pow(aPrimitive1.Position().z - aPrimitive2.Position().z, 2.0));
//
//		float minDistance = sphere1.Radius() + sphere2.Radius();
//		minDistance *= minDistance;
//
//		if (distance <= minDistance)
//			return true;
//	}
//	
//	return intersect;
//}

bool PhysicsEngine::Intersect(Primitive* aPrimitive1, Primitive* aPrimitive2)
{
	bool intersect = false;

	if (aPrimitive1->Type() == EPrimitiveType::SPHERE_TYPE && aPrimitive2->Type() == EPrimitiveType::SPHERE_TYPE)
	{
		Sphere* sphere1 = static_cast<Sphere*>(aPrimitive1);
		Sphere* sphere2 = static_cast<Sphere*>(aPrimitive2);

		float distance = sqrt(pow(aPrimitive1->Position().x - aPrimitive2->Position().x, 2.0) + pow(aPrimitive1->Position().y - aPrimitive2->Position().y, 2.0) + pow(aPrimitive1->Position().z - aPrimitive2->Position().z, 2.0));

		float minDistance = sphere1->Radius() + sphere2->Radius();
		minDistance *= minDistance;

		if (distance <= minDistance)
			return true;
	}

	return intersect;
}
