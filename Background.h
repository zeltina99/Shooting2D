#pragma once
#include "Actor.h"

class Background : public Actor
{
public:
	Background() = delete;
	Background(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.
	~Background();

	virtual void Tick(float InDeltaTime) override;
	virtual void Render(Gdiplus::Graphics* InGraphics) override;

private:
	static constexpr int PixelSize = 64;

	// 중심점
	//PointF Pivot = { 0.5f, 0.5f };	// Pivot 기본 값은 한가운데

	// 위치
	//PointF Position = { 0.0f, 0.0f };

	// 이동 속도
	//float Speed = 50.0f;

	// 이미지가 들어있을 비트맵
	//Gdiplus::Bitmap* Image = nullptr;   

	float Offset = 0.0f;
};

