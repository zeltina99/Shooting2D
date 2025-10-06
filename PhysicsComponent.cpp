#include "PhysicsComponent.h"
#include "Actor.h"


bool PhysicsComponent::IsCollision(PhysicsComponent* InOther) const
{
	bool Result = false;	// 기본 결과값: 충돌 아님

	if (!InOther || InOther == this)	// 상대가 없거나 자기 자신이면
	{
		return Result;	// 충돌 아니므로 종료
	}

	if(this->GetLayer() == PhysicsLayer::None || InOther->GetLayer() == PhysicsLayer::None)
	{
		return Result;	// 물리 레이어가 None이면 충돌 계산 대상 아님
	}
	
	if (Collision == InOther->GetCollitionType())	// 두 컴포넌트의 충돌 모양이 같다면
	{
		switch (Collision)	// 모양에 따라 분기
		{
		case CollisionType::Circle:
			Result = CheckCircletToCircleCollision(this, InOther);	// 원ㅡ원
			break;
		case CollisionType::Rectangle:
			Result = CheckRectToRectCollision(this, InOther);	// 사각형ㅡ사각형(AABB)
			break;
		}
	}
	// 모양이 다르면
	else
	{
		Result = CheckCircletToRectCollision(this, InOther);	// 원ㅡ사각형 처리
	}

	return Result;	// 최종 충돌 여부 반환
}

bool PhysicsComponent::CheckCircletToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)	// 안전성 체크
	{
		return false;
	}

	const PointF& From = InFrom->GetOwner()->GetPosition();	// 원1의 중심 좌표
	const PointF& To = InTo->GetOwner()->GetPosition();		// 원2의 중심 좌표

	float dx = To.X - From.X;								// 두 중심 간 x 차
	float dy = To.Y - From.Y;								// 두 중심 간 y 차
	float squaredDistance = dx * dx + dy * dy;				// 거리^2 (루트 피하기 위한 최적화)

	float radiusSum = InFrom->GetRadius() + InTo->GetRadius();	// 반지름 합
	float squaredRadiusSum = radiusSum * radiusSum;				// (반지름 합)^2

	return squaredDistance <= squaredRadiusSum;		// 거리^2 <= (반지름 합)^2 이면 접촉/충돌
}

bool PhysicsComponent::CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo)
{
	if (!InFrom || !InTo)			// 안전성 체크
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

	const PointF& From = Rect->GetOwner()->GetPosition();		// 사각형
	const PointF& To = Circle->GetOwner()->GetPosition();			// 원

	float RectLeft = From.X - Rect->GetWidth() * 0.5f;		// 사각형의 꼭지점
	float RectRight = From.X + Rect->GetWidth() * 0.5f;
	float RectTop = From.Y - Rect->GetHeight() * 0.5f;
	float RectBottom = From.Y + Rect->GetHeight() * 0.5f;

	//원의 중심에서 사각형에 가장 가까운 점 찾기
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
