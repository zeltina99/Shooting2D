#include "PhysicsComponent.h"
#include "Actor.h"


bool PhysicsComponent::IsCollision(PhysicsComponent* InOther) const
{
	bool Result = false;

	if (!InOther || InOther == this)
	{
		return Result;
	}

	if(this->GetLayer() == PhysicsLayer::None || InOther->GetLayer() == PhysicsLayer::None)
	{
		return Result;
	}
	
	if (Collision == InOther->GetCollitionType())
	{
		switch (Collision)
		{
		case CollisionType::Circle:
			Result = CheckCircletToCircleCollision(this, InOther);
			break;
		case CollisionType::Rectangle:
			Result = CheckRectToRectCollision(this, InOther);
			break;
		}
	}
	else
	{
		Result = CheckCircletToRectCollision(this, InOther);
	}

	return Result;
}

bool PhysicsComponent::CheckCircletToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)
	{
		return false;
	}

	const PointF& From = InFrom->GetOwner()->GetPosition();
	const PointF& To = InTo->GetOwner()->GetPosition();

	float dx = To.X - From.X;
	float dy = To.Y - From.Y;
	float squaredDistance = dx * dx + dy * dy;

	float radiusSum = InFrom->GetRadius() + InTo->GetRadius();
	float squaredRadiusSum = radiusSum * radiusSum;

	return squaredDistance <= squaredRadiusSum;
}

bool PhysicsComponent::CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)
	{
		return false;
	}

	const PointF& From = InFrom->GetOwner()->GetPosition();
	const PointF& To = InTo->GetOwner()->GetPosition();

	float HalfWidthFrom = InFrom->GetWidth() * 0.5f;
	float HalfHeightFrom = InFrom->GetHeight() * 0.5f;
	float HalfWidthTo = InTo->GetWidth() * 0.5f;
	float HalfHeightTo = InTo->GetHeight() * 0.5f;

	float FromLeft = From.X - HalfWidthFrom;
	float FromRight = From.X + HalfWidthFrom;
	float FromTop = From.Y - HalfHeightFrom;
	float FromBottom = From.Y + HalfHeightFrom;

	float ToLeft = To.X - HalfWidthTo;
	float ToRight = To.X + HalfWidthTo;
	float ToTop = To.Y - HalfHeightTo;
	float ToBottom = To.Y + HalfHeightTo;

	return !(FromRight < ToLeft || FromLeft > ToRight || FromBottom < ToTop || FromTop > ToBottom);
}

bool PhysicsComponent::CheckCircletToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)
	{
		return false;
	}

	const PhysicsComponent* Circle;
	const PhysicsComponent* Rect;

	if (InFrom->GetCollitionType() == CollisionType::Circle)
	{
		Circle = InFrom;
		Rect = InTo;
	}
	else
	{
		Circle = InTo;
		Rect = InFrom;
	}

	const PointF& From = Rect->GetOwner()->GetPosition();		// �簢��
	const PointF& To = Circle->GetOwner()->GetPosition();			// ��

	float RectLeft = From.X - Rect->GetWidth() * 0.5f;		// �簢���� ������
	float RectRight = From.X + Rect->GetWidth() * 0.5f;
	float RectTop = From.Y - Rect->GetHeight() * 0.5f;
	float RectBottom = From.Y + Rect->GetHeight() * 0.5f;

	//���� �߽ɿ��� �簢���� ���� ����� �� ã��
	float ClosestX = To.X;
	float ClosestY = To.Y;

	if (To.X < RectLeft)
	{
		ClosestX = RectLeft;
	}
	else if (To.X > RectRight)
	{
		ClosestX = RectRight;
	}

	if (To.Y < RectTop)
	{
		ClosestY = RectTop;
	}
	else if (To.Y > RectBottom)
	{
		ClosestY = RectBottom;
	}

	float dx = To.X - ClosestX;
	float dy = To.Y - ClosestY;
	float squaredDistance = dx * dx + dy * dy;

	return squaredDistance <= (Circle->GetRadius() * Circle->GetRadius());
}
