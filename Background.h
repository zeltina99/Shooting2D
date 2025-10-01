#pragma once
#include "Common.h"


class Background
{
public:
	Background() = delete;
	Background(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
	~Background();

	void Tick(float InDeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);

private:
	static constexpr int PixelSize = 64;

	// �߽���
	PointF Pivot = { 0.5f, 0.5f };	// Pivot �⺻ ���� �Ѱ��

	// ��ġ
	PointF Position = { 0.0f, 0.0f };

	// �̵� �ӵ�
	float Speed = 50.0f;

	// �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   

	float Offset = 0.0f;
};

