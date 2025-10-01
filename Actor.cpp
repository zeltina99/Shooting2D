#include "Actor.h"

Actor::Actor(const wchar_t* InImagePath)
{
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
        // g_PlayerImage�� �ε��Ǿ� �ִ�.
        InGraphics->DrawImage(
            Image,                  // �׷��� �̹���
            static_cast<int>(Position.X - PixelSize * Pivot.X),
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),               // �׷��� ��ġ
            PixelSize, PixelSize);  // �׷��� ������
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
