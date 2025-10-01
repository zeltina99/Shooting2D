#include "Player.h"
#include "Background.h"

Player::Player(const wchar_t* InImagePath)
    : Actor(InImagePath)
{
    Position.X = 300.0f;
    Position.Y = 700.0f;
    KeyWasPressedMap[InputDirection::Up] = false;
	KeyWasPressedMap[InputDirection::Down] = false;
	KeyWasPressedMap[InputDirection::Left] = false;
	KeyWasPressedMap[InputDirection::Right] = false;
}

void Player::OnTick(float InDeltaTime)
{
    float MoveDistance = InDeltaTime * Speed;
    if (KeyWasPressedMap[InputDirection::Left])
    {
        Position.X -= MoveDistance;
    }
    if (KeyWasPressedMap[InputDirection::Right])
    {
        Position.X += MoveDistance;
    }
    if (Position.X < (0 - Size * 0.5f))
    {
        Position.X = g_ScreenSize.X + Size * 0.5f; // 순환 이동
    }
    else if ((g_ScreenSize.X + Size * 0.5f) < Position.X)
    {
        Position.X = static_cast<float>(0 - Size * 0.5f);
    }
}


void Player::OnRender(Gdiplus::Graphics* InGraphics)
{
    Actor::OnRender(InGraphics);        // 부모의 OnRender 실행

    // 부모의 OnRender 실행한 후 추가로 동작 실행
    if (!Image)
    {
        // g_PlayerImage가 로딩되어 있다.
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,                  // 그려질 이미지
            static_cast<int>(Position.X - Size * Pivot.X),
            static_cast<int>(Position.Y - Size * Pivot.Y),               // 그려질 위치
            Size, Size);  // 그려질 사이즈
    }
    
}

void Player::HandleKeyState(WPARAM InKey, bool InIsPressed)
{

    if (InKey == VK_LEFT || InKey == VK_RIGHT)
    {
        KeyWasPressedMap[static_cast<InputDirection>(InKey)] = InIsPressed;

        //if ((InKey == VK_LEFT)&& InIsPressed)
        //{
        //    Position.X -= Speed;
        //    if (Position.X < (0 - PixelSize * 0.5f) )
        //    {
        //        Position.X = g_ScreenSize.X + PixelSize * 0.5f; // 순환 이동
        //    }
        //    //InvalidateRect(g_hMainWindow, nullptr, FALSE);
        //}
        //else if ((InKey == VK_RIGHT)&& InIsPressed)
        //{
        //    Position.X += Speed;
        //    if ((g_ScreenSize.X + PixelSize * 0.5f) < Position.X)
        //    {
        //        Position.X = static_cast<float>(0 - PixelSize * 0.5f);
        //    }

        //    //InvalidateRect(g_hMainWindow, nullptr, FALSE);
        //}
    }
}
