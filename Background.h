#pragma once
#include "Actor.h"

class Background : public Actor
{
public:
	Background() = delete;
	Background(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
	~Background();

	virtual void Tick(float InDeltaTime) override;
	virtual void Render(Gdiplus::Graphics* InGraphics) override;

private:
	static constexpr int PixelSize = 64;

	// �߽���
	//PointF Pivot = { 0.5f, 0.5f };	// Pivot �⺻ ���� �Ѱ��

	// ��ġ
	//PointF Position = { 0.0f, 0.0f };

	// �̵� �ӵ�
	//float Speed = 50.0f;

	// �̹����� ������� ��Ʈ��
	//Gdiplus::Bitmap* Image = nullptr;   

	float Offset = 0.0f;
};

