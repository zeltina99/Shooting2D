#pragma once
#include <unordered_map>
#include "Common.h"
#include "enums.h"

class Actor
{
public:

	Actor() = delete;
	Actor(const wchar_t* InImagePath);
	virtual ~Actor();

	virtual void Tick(float InDeltaTime) = 0;
	virtual void Render(Gdiplus::Graphics* InGraphics);

	const PointF& GetPosition() const { return Position; }
	float GetSpeed() const { return Speed; }

protected:
	void SetPosition(const PointF& InPosition);
	void SetSpeed(const float& InSpeed);
	void SetPivot(const PointF& InPivotX);

	// ũ��
	static constexpr int PixelSize = 64;

	// �߽���
	PointF Pivot = { 0.5f, 0.5f };

	// ��ġ
	PointF Position = { 0.0f, 0.0f };

	// �̵� �ӵ�
	float Speed = 0.0f;

	Gdiplus::Bitmap* Image = nullptr;
};

