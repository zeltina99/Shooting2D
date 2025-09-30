#include "BackGround.h"


BackGround::BackGround(const wchar_t* InImagePath)
{
    Position.X = 0;
    Position.Y = 0;

    BGImage = new Gdiplus::Bitmap(InImagePath);  // 플레이어 이미지 로딩
    if (BGImage->GetLastStatus() != Gdiplus::Ok)
    {
        // 정상적으로 파일 로딩이 안됬다.
        delete BGImage;           // 실패했으면 즉시 해제
        BGImage = nullptr;
        OutputDebugString(L"플레이어 이미지 로드 실패");
        MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
    }
}

BackGround::~BackGround()
{
    if (BGImage)
    {
        delete BGImage;
        BGImage = nullptr;
    }
}

void BackGround::BackRender(Gdiplus::Graphics* Graphics)
{
    if (!BGImage) 
    {
        return;
    }

    const int ImgWidth = BGImage->GetWidth();
    const int ImgHeight = BGImage->GetHeight();

    // 화면 전체를 타일처럼 채움
    for (int y = -ImgHeight; y < g_ScreenSize.Y; y += ImgHeight)
    {
        for (int x = 0; x < g_ScreenSize.X; x += ImgWidth)
        {
            int drawY = y + OffsetY;
            Graphics->DrawImage(BGImage, x, drawY, ImgWidth, ImgHeight);
        }
    }

    // 스크롤 이동
    OffsetY = (OffsetY + ScrollSpeed) % ImgHeight;
}

