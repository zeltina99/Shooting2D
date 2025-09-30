#include "Player.h"

Player::Player(const wchar_t* InImagePath)
{
    Position.X = 300;
    Position.Y = 700;

	KeyWasPressedMap[InputDirection::Up] = false;
	KeyWasPressedMap[InputDirection::Down] = false;
	KeyWasPressedMap[InputDirection::Left] = false;
	KeyWasPressedMap[InputDirection::Right] = false;

    Image = new Gdiplus::Bitmap(InImagePath);  // �÷��̾� �̹��� �ε�
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        // ���������� ���� �ε��� �ȉ��.
        delete Image;           // ���������� ��� ����
        Image = nullptr;
        OutputDebugString(L"�÷��̾� �̹��� �ε� ����");
        MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
    }
}

Player::~Player()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Player::Render(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        // g_PlayerImage�� �ε��Ǿ� �ִ�.
        InGraphics->DrawImage(
            Image,                  // �׷��� �̹���
            static_cast<int>(Position.X - PixelSize * Pivot.X),
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),               // �׷��� ��ġ
            PixelSize, PixelSize);  // �׷��� ������
    }
    else
    {
        // �÷��̾� �̹����� ������ ���� ��� �׸�
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            100, 100,
            PixelSize, PixelSize);
    }
}

void Player::HandleKeyState(WPARAM InKey, bool InIsPressed)
{

    if (InKey == VK_LEFT || InKey == VK_RIGHT)
    {
        KeyWasPressedMap[static_cast<InputDirection>(InKey)] = InIsPressed;

        if (InKey == VK_LEFT)
        {
            Position.X -= Speed;
            if (Position.X < (0 + PixelSize))
            {
                Position.X = 0 + PixelSize;
            }
            InvalidateRect(g_hMainWindow, nullptr, FALSE);
        }
        else if (InKey == VK_RIGHT)
        {
            Position.X += Speed;
            if ((g_ScreenSize.X - PixelSize) < Position.X)
            {
                Position.X = static_cast<float>(g_ScreenSize.X - PixelSize);
            }

            InvalidateRect(g_hMainWindow, nullptr, FALSE);
        }
    }
}
