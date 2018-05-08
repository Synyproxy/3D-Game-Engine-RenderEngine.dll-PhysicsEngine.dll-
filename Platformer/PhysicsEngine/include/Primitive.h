#pragma once

#include "stdafx.h"
#include "Utils.h"


namespace Physics
{
	enum PHYSICS EPrimitiveType
	{
		UNKNOWN_TYPE,
		RAY_TYPE,
		SPHERE_TYPE,
		PLANE_TYPE,
		TRIANGLE_TYPE,
		AABB_TYPE,
		OBB_TYPE,
	};

	struct PHYSICS AABB;

	struct PHYSICS Primitive
	{
		virtual EPrimitiveType	GetType()																				const = 0;
		virtual void			Transform(Transformation& transformMatrix, Primitive* aTransformedPrimitive)				const = 0;
	};

	struct PHYSICS Ray final: public Primitive
	{
		glm::vec3		Origin;
	glm::vec3		Direction;

	Ray(const glm::vec3& aOrigin = { 0.0f,0.0f,0.0f }, const glm::vec3& aDirection = { 0.0f,0.0f,1.0f });

	EPrimitiveType			GetType()																				const override { return RAY_TYPE; };
	void					Transform(Transformation& transformMatrix, Primitive* aTransformedPrimitive)				const override { assert(false); /*Not Implemented yet*/ }

	bool					operator!=	(const Ray& other)																const { return Origin != other.Origin || Direction != other.Direction; }
	};

	struct PHYSICS Sphere final: public Primitive
	{
		glm::vec3		Center;
	float			Radius;

	Sphere(const glm::vec3& aCenter = { 0.0f, 0.0f, 0.0f }, float aRadius = 1.0f);
	Sphere(const AABB& aBoundingBox);

	EPrimitiveType	GetType() const override { return SPHERE_TYPE; }
	void			Transform(Transformation& atransformMatrix, Primitive* aTransformedPrimitive)							const override;
	};

	struct PHYSICS Triangle final: public Primitive
	{
		glm::vec3		Point[3];

	Triangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
	Triangle(const glm::vec3* aPointArray);

	EPrimitiveType	GetType()																							const override { return TRIANGLE_TYPE; };
	void			Transform(Transformation& aTransformMatrix, Primitive* aTransformedPrimitive)							const override { assert(false); /*Not Implemented*/ }
	};

	struct PHYSICS AABB : public Primitive
	{
		enum EFace
		{
			LEFT,
			RIGHT,
			FRONT,
			BACK,
			TOP,
			BOTTOM,

			COUNT
		};

		static const glm::vec3 AABBFaceNormal[COUNT];

		glm::vec3				PointMin;
		glm::vec3				PointMax;

		AABB(const glm::vec3& aPointMin = { -0.5f,-0.5f,-0.5f }, const glm::vec3& aPointMax = { 0.5f,0.5f,0.5f });

		void					Merge(const AABB& aOtherAABB);
		void					Merge(const glm::vec3& aPoint);

		inline bool				IsPointInside(const glm::vec3& aPoint)		const { return glm::clamp(aPoint, PointMin, PointMax) == aPoint; }
		bool					FindEdges(const glm::vec3& aPoint, Ray& aRay) const;

		virtual EPrimitiveType	GetType()																					const override { return AABB_TYPE; };
		virtual void			Transform(Transformation& aTransformMatrix, Primitive* aTransformedPrimitive)			const override;

	private:
		bool					FindCommonEdge(const Ray& anEdge, const Ray* const anEdgeArray, unsigned int anEdgeCount)	const;
	};

	struct PHYSICS OBB final : public AABB
	{
		AABB			AbsoluteBoundingBox;
	glm::mat4x4		OBBtoAABB;
	glm::mat4x4		AABBtoOBB;

	OBB(const AABB& aBoundingBox);
	OBB(const glm::vec3& aPointMin = { -0.5f,-0.5f,-0.5f }, const glm::vec3& aPointMax = { 0.5f, 0.5f, 0.5f });

	EPrimitiveType	GetType()																						const override { return OBB_TYPE; };
	void			Transform(Transformation& aTransformMatrix, Primitive* aTransformedPrimitive)						const override;
	};

	struct PHYSICS Plane final: public Primitive
	{
		glm::vec3	Normal;
	glm::vec3	Point;

	Plane(const glm::vec3& aPoint = { 0.0f,0.0f,0.0f }, const glm::vec3& aNormal = { 0.0f, 1.0f,0.0f });
	Plane(const Triangle& aTriangle);
	Plane(const AABB& aBox, AABB::EFace aFace);

	EPrimitiveType	GetType() const override { return PLANE_TYPE; };
	void			Transform(Transformation& aTransformMatrix, Primitive* aTransformedPrimitive)						const override { assert(false); /* Not implemented*/ }
	};
}