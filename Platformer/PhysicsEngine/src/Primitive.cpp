#include "stdafx.h"
#include "Primitive.h"
#include <assert.h>
#include "Utils.h"

using namespace Physics;

Ray::Ray(const glm::vec3& aOrigin, const glm::vec3& aDirection) : Origin(aOrigin), Direction(glm::normalize(aDirection))
{
	assert(Direction != glm::vec3());
}

Sphere::Sphere(const glm::vec3& aCenter, float aRadius) : Center(aCenter), Radius(aRadius)
{
	assert(Radius > 0.0f);
}

Sphere::Sphere(const AABB& aBoundingBox) : Center((aBoundingBox.PointMin + aBoundingBox.PointMax) * 0.5f), Radius(glm::length(aBoundingBox.PointMax - aBoundingBox.PointMin) * 0.5f)
{

}

void Sphere::Transform(Transformation& aTransform, Primitive* aTransformedPrimitive) const
{
	if (!aTransformedPrimitive)
	{
		aTransformedPrimitive = new Sphere(*this);
	}
	Sphere* transformedSphere = static_cast<Sphere*>(aTransformedPrimitive);
	transformedSphere->Center = Center + aTransform.GetPosition();
	transformedSphere->Radius = Radius * Utils::Max3(aTransform.GetScale());
}

Triangle::Triangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C)
{
	assert(A != B && B != C && A != C);
	Point[0] = A; Point[1] = B; Point[2] = C;
}

Triangle::Triangle(const glm::vec3* aPointArray)
{
	assert(aPointArray);
	assert(aPointArray[0] != aPointArray[1] && aPointArray[0] != aPointArray[2] && aPointArray[1] != aPointArray[2]);
	memcpy(Point, aPointArray, 3 * sizeof(glm::vec3));
}

Plane::Plane(const glm::vec3& aPoint, const glm::vec3& aNormal)
	: Point(aPoint)
	, Normal(aNormal)
{
	assert(Normal != glm::vec3());
}

Plane::Plane(const Triangle& aTriangle)
	: Point(aTriangle.Point[0])
{
	Normal = glm::normalize(glm::cross(aTriangle.Point[1] - aTriangle.Point[0], aTriangle.Point[2] - aTriangle.Point[0]));
	assert(Normal != glm::vec3());
}

Plane::Plane(const AABB& aBox, AABB::EFace aFace) : Normal(AABB::AABBFaceNormal[aFace])
{
	Point.x = (aFace == AABB::LEFT) ? aBox.PointMin.x : aBox.PointMax.x;
	Point.y = (aFace == AABB::BOTTOM) ? aBox.PointMin.y : aBox.PointMax.y;
	Point.z = (aFace == AABB::BACK) ? aBox.PointMin.z : aBox.PointMax.z;
}

const glm::vec3 AABB::AABBFaceNormal[AABB::COUNT] = {
	{ -1.0f, 0.0f, 0.0f },	// LEFT
{ 1.0f, 0.0f, 0.0f },	// RIGHT
{ 0.0f, 0.0f, 1.0f },	// FRONT
{ 0.0f, 0.0f, -1.0f },	// BACK
{ 0.0f, 1.0f, 0.0f },	// TOP
{ 0.0f, -1.0f, 0.0f },	// BOTTOM
};

AABB::AABB(const glm::vec3& aPointMin, const glm::vec3& aPointMax)
	: PointMin(aPointMin)
	, PointMax(aPointMax)
{
	assert(glm::min(aPointMin, aPointMax) == aPointMin);
	assert(glm::max(aPointMin, aPointMax) == aPointMax);
}

void AABB::Merge(const AABB& aOtherAABB)
{
	PointMin = glm::min(PointMin, aOtherAABB.PointMin);
	PointMax = glm::max(PointMax, aOtherAABB.PointMax);
}

void AABB::Merge(const glm::vec3& aPoint)
{
	PointMin = glm::min(PointMin, aPoint);
	PointMax = glm::max(PointMax, aPoint);
}

void AABB::Transform(Transformation& aTransformationMatrix, Primitive* aTransformedPrimitive) const
{
	if (!aTransformedPrimitive)
	{
		aTransformedPrimitive = new AABB(*this);
	}
	AABB* transformedBox = static_cast<AABB*>(aTransformedPrimitive);
	transformedBox->PointMin = aTransformationMatrix.GetScale() * PointMin + aTransformationMatrix.GetPosition();
	transformedBox->PointMax = aTransformationMatrix.GetScale() * PointMax + aTransformationMatrix.GetPosition();
}

bool AABB::FindEdges(const glm::vec3& aPoint, Ray& aRay) const
{
	assert(IsPointInside(aPoint));
	aRay.Origin = PointMin;
	aRay.Direction = glm::vec3(1.0f, 1.0f, 1.0f);

	for (unsigned int dim = 0; dim < 3; ++dim)
	{
		if (aPoint[dim] == PointMin[dim])
		{
			aRay.Origin[dim] = PointMin[dim];
			aRay.Direction[dim] = 0.0f;
		}
		else if (aPoint[dim] == PointMax[dim])
		{
			aRay.Origin[dim] = PointMax[dim];
			aRay.Direction[dim] = 0.0f;
		}
	}

	return aRay.Direction == glm::vec3() || aRay.Direction == XAxis || aRay.Direction == YAxis || aRay.Direction == ZAxis;
}

OBB::OBB(const AABB& aBoundingBox)
	: AABB(aBoundingBox)
	, AbsoluteBoundingBox(aBoundingBox)
{
}

OBB::OBB(const glm::vec3& aPointMin, const glm::vec3& aPointMax)
	: AABB(aPointMin, aPointMax)
	, AbsoluteBoundingBox(aPointMin, aPointMax)
{
}

void OBB::Transform(Transformation& aTransformationMatrix, Primitive* aTransformedPrimitive) const
{
	if (!aTransformedPrimitive)
	{
		aTransformedPrimitive = new OBB(*this);
	}
	OBB* transformedBox = static_cast<OBB*>(aTransformedPrimitive);
	transformedBox->PointMin = aTransformationMatrix.GetScale() * PointMin;
	transformedBox->PointMax = aTransformationMatrix.GetScale() * PointMax;

	// Transform 8 corners of the box
	transformedBox->AbsoluteBoundingBox.PointMin = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	transformedBox->AbsoluteBoundingBox.PointMax = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	const glm::mat4x4 matrix = aTransformationMatrix.GetMatrix();
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMin, 1.0f));
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMin.x, PointMin.y, PointMax.z, 1.0f));
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMin.x, PointMax.y, PointMin.z, 1.0f));
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMin.x, PointMax.y, PointMax.z, 1.0f));
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMax.x, PointMin.y, PointMax.z, 1.0f));
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMax.x, PointMax.y, PointMin.z, 1.0f));
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMax.x, PointMin.y, PointMin.z, 1.0f));
	transformedBox->AbsoluteBoundingBox.Merge(matrix * glm::vec4(PointMax, 1.0f));

	const glm::vec3& translation = aTransformationMatrix.GetPosition();
	const glm::vec3& rotation = aTransformationMatrix.GetRotation();

	transformedBox->AABBtoOBB = glm::mat4x4();
	Transformation::ApplyRotation(rotation.y, YAxis, transformedBox->AABBtoOBB);
	Transformation::ApplyRotation(rotation.x, XAxis, transformedBox->AABBtoOBB);
	Transformation::ApplyRotation(rotation.z, ZAxis, transformedBox->AABBtoOBB);

	memcpy(&transformedBox->AABBtoOBB[3], &translation[0], 3 * sizeof(float));

	// Compute inverse rotation
	// Original rotation = RotZ * RotX * RotY
	// Inverse rotation = RotY-1 * RotX-1 * RotZ-1
	transformedBox->OBBtoAABB = glm::mat4x4();
	Transformation::ApplyRotation(-rotation.z, ZAxis, transformedBox->OBBtoAABB);
	Transformation::ApplyRotation(-rotation.x, XAxis, transformedBox->OBBtoAABB);
	Transformation::ApplyRotation(-rotation.y, YAxis, transformedBox->OBBtoAABB);

	transformedBox->OBBtoAABB = transformedBox->OBBtoAABB * glm::translate(-translation);
}