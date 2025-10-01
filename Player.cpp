#include "Player.h"
#include "Background.h"

Player::Player(const wchar_t* InImagePath) : Actor(InImagePath)
{
    SetSpeed(200.0f);

    SetPosition({ 300, 700 });

	KeyWasPressedMap[InputDirection::Up] = false;
	KeyWasPressedMap[InputDirection::Down] = false;
	KeyWasPressedMap[InputDirection::Left] = false;
	KeyWasPressedMap[InputDirection::Right] = false;


}

Player::~Player()
{
  
}

void Player::Tick(float InDeltaTime)
{
    float MoveDistance = InDeltaTime * GetSpeed();
    PointF CurrentPos = GetPosition();

    if (KeyWasPressedMap[InputDirection::Left])
    {
        CurrentPos.X -= MoveDistance;
    }
    if (KeyWasPressedMap[InputDirection::Right])
    {
        CurrentPos.X += MoveDistance;
    }

    if (CurrentPos.X < (0 - PixelSize * 0.5f))
    {
        CurrentPos.X = g_ScreenSize.X + PixelSize * 0.5f;
    }
    else if ((g_ScreenSize.X + PixelSize * 0.5f) < CurrentPos.X)
    {
        CurrentPos.X = 0 - PixelSize * 0.5f;
    }

    SetPosition(CurrentPos);
}


void Player::Render(Gdiplus::Graphics* InGraphics)
{
    Actor::Render(InGraphics);
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
