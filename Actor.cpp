#include "Actor.h"

Actor::Actor(const wchar_t* InImagePath)
{
    Image = new Gdiplus::Bitmap(InImagePath);  // 플레이어 이미지 로딩
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        // 정상적으로 파일 로딩이 안됬다.
        delete Image;           // 실패했으면 즉시 해제
        Image = nullptr;
        OutputDebugString(L"플레이어 이미지 로드 실패");
        MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
    }
}

Actor::~Actor()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Actor::Render(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        // g_PlayerImage가 로딩되어 있다.
        InGraphics->DrawImage(
            Image,                  // 그려질 이미지
            static_cast<int>(Position.X - PixelSize * Pivot.X),
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),               // 그려질 위치
            PixelSize, PixelSize);  // 그려질 사이즈
    }
}

void Actor::SetPosition(const PointF& InPosition)
{
    Position = InPosition;
}

void Actor::SetSpeed(const float& InSpeed)
{
    Speed = InSpeed;
}

void Actor::SetPivot(const PointF& InPivot)
{
    Pivot = InPivot;

}
