#include "PhysicsComponent.h"
#include "Actor.h"


bool PhysicsComponent::IsCollision(PhysicsComponent* InOther) const
{
	bool Result = false;	// �⺻ �����: �浹 �ƴ�

	if (!InOther || InOther == this)	// ��밡 ���ų� �ڱ� �ڽ��̸�
	{
		return Result;	// �浹 �ƴϹǷ� ����
	}

	if(this->GetLayer() == PhysicsLayer::None || InOther->GetLayer() == PhysicsLayer::None)
	{
		return Result;	// ���� ���̾ None�̸� �浹 ��� ��� �ƴ�
	}
	
	if (Collision == InOther->GetCollitionType())	// �� ������Ʈ�� �浹 ����� ���ٸ�
	{
		switch (Collision)	// ��翡 ���� �б�
		{
		case CollisionType::Circle:
			Result = CheckCircletToCircleCollision(this, InOther);	// ���ѿ�
			break;
		case CollisionType::Rectangle:
			Result = CheckRectToRectCollision(this, InOther);	// �簢���ѻ簢��(AABB)
			break;
		}
	}
	// ����� �ٸ���
	else
	{
		Result = CheckCircletToRectCollision(this, InOther);	// ���ѻ簢�� ó��
	}

	return Result;	// ���� �浹 ���� ��ȯ
}

bool PhysicsComponent::CheckCircletToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)	// ������ üũ
	{
		return false;
	}

	const PointF& From = InFrom->GetOwner()->GetPosition();	// ��1�� �߽� ��ǥ
	const PointF& To = InTo->GetOwner()->GetPosition();		// ��2�� �߽� ��ǥ

	float dx = To.X - From.X;								// �� �߽� �� x ��
	float dy = To.Y - From.Y;								// �� �߽� �� y ��
	float squaredDistance = dx * dx + dy * dy;				// �Ÿ�^2 (��Ʈ ���ϱ� ���� ����ȭ)

	float radiusSum = InFrom->GetRadius() + InTo->GetRadius();	// ������ ��
	float squaredRadiusSum = radiusSum * radiusSum;				// (������ ��)^2

	return squaredDistance <= squaredRadiusSum;		// �Ÿ�^2 <= (������ ��)^2 �̸� ����/�浹
}

bool PhysicsComponent::CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)			// ������ üũ
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
