#pragma once
#include <unordered_map>
#include <windows.h>
#include <gdiplus.h>
#include "enums.h"

extern HWND g_hMainWindow;	// g_hMainWindow가 다른 파일에 있다는 것을 알려줌
extern Gdiplus::Point g_ScreenSize;



class BackGround
{
public:
	BackGround() = delete;
	BackGround(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.
	~BackGround();

	void BackRender(Gdiplus::Graphics* Graphics);

private:
	static constexpr int BackPixelSize = 64;

	int OffsetY = 0;
	static constexpr int ScrollSpeed = 2;

	// 배경 오브젝트의 위치
	Gdiplus::PointF Position = { 0.0f, 0.0f };

	// 배경 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* BGImage = nullptr;	// 배경이 그려질 종이


};

