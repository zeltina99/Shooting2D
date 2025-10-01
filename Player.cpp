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
        Position.X = g_ScreenSize.X + Size * 0.5f; // ��ȯ �̵�
    }
    else if ((g_ScreenSize.X + Size * 0.5f) < Position.X)
    {
        Position.X = static_cast<float>(0 - Size * 0.5f);
    }
}


void Player::OnRender(Gdiplus::Graphics* InGraphics)
{
    Actor::OnRender(InGraphics);        // �θ��� OnRender ����

    // �θ��� OnRender ������ �� �߰��� ���� ����
    if (!Image)
    {
        // g_PlayerImage�� �ε��Ǿ� �ִ�.
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,                  // �׷��� �̹���
            static_cast<int>(Position.X - Size * Pivot.X),
            static_cast<int>(Position.Y - Size * Pivot.Y),               // �׷��� ��ġ
            Size, Size);  // �׷��� ������
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
        //        Position.X = g_ScreenSize.X + PixelSize * 0.5f; // ��ȯ �̵�
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
