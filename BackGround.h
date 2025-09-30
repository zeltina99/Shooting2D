#pragma once
#include <unordered_map>
#include <windows.h>
#include <gdiplus.h>
#include "enums.h"

extern HWND g_hMainWindow;	// g_hMainWindow�� �ٸ� ���Ͽ� �ִٴ� ���� �˷���
extern Gdiplus::Point g_ScreenSize;



class BackGround
{
public:
	BackGround() = delete;
	BackGround(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
	~BackGround();

	void BackRender(Gdiplus::Graphics* Graphics);

private:
	static constexpr int BackPixelSize = 64;

	int OffsetY = 0;
	static constexpr int ScrollSpeed = 2;

	// ��� ������Ʈ�� ��ġ
	Gdiplus::PointF Position = { 0.0f, 0.0f };

	// ��� �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* BGImage = nullptr;	// ����� �׷��� ����


};

