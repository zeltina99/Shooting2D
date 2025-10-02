#pragma once
#include "Component.h"
#include "enums.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Actor* InOwner, CollisionType InType = CollisionType::Circle, PhysicsLayer InLayer = PhysicsLayer::None)
		:Component(InOwner), Collision(InType), Layer(InLayer)
	{

	}

	bool IsCollision(PhysicsComponent* InOther) const;

	inline float GetRadius() const { return Data1; }
	inline float GetWidth() const { return Data1; }
	inline float GetHeight() const { return Data2; }
	inline CollisionType GetCollitionType()const{ return Collision; }
	inline PhysicsLayer GetLayer() const { return Layer; }

	inline void SetRadius(float radius) { Data1 = radius; }
	inline void SetWidth(float width) { Data1 = width; }
	inline void SetHeight(float height) { Data1 = height; }


private:
	static bool CheckCircletToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckCircletToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);

	CollisionType Collision = CollisionType::Circle;
	PhysicsLayer Layer = PhysicsLayer::None;
	float Data1 = 0.0f;
	float Data2 = 0.0f;
};

