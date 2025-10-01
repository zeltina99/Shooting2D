#pragma once
#include "Common.h"

class Actor
{
public:
	Actor() = delete;
	Actor(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
	virtual ~Actor();

	virtual void OnTick(float InDeltaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);

	// Getter
	inline const PointF& GetPosition() const { return Position; }
	inline int GetSize() const { return Size; }
	inline const PointF& GetPivot() const { return Pivot; }

	// Setter
	inline void SetPosition(float InX, float InY) { Position.X = InX; Position.Y = InY; }
	inline void SetSize(int InSize) { Size = InSize; }
	inline void SetPivot(float InX, float InY) { Pivot.X = InX; Pivot.Y = InY; }
	inline void SetRenderLayer(RenderLayer InLayer) { TargetRenderLayer = InLayer; }

protected:
	// ��ġ
	PointF Position = { 0.0f, 0.0f };

	// ũ��
	int Size = 64;

	// �߽���
	PointF Pivot = { 0.5f, 0.5f }; // Pivot �⺻ ���� �Ѱ��

	// �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����		

	// �̹����� �׷��� ���̾�
	RenderLayer TargetRenderLayer = RenderLayer::Misc;

};

