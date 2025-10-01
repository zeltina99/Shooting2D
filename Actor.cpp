#include "Actor.h"

Actor::Actor(const wchar_t* InImagePath)
{
    if(InImagePath)
    {
        Image = new Gdiplus::Bitmap(InImagePath);  //  �̹��� �ε�
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // ���������� ���� �ε��� �ȉ��.
            delete Image;           // ���������� ��� ����
            Image = nullptr;
            OutputDebugString(L"�÷��̾� �̹��� �ε� ����");
            MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
        }
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

void Actor::OnTick(float InDeltaTime)
{

}

void Actor::OnRender(Gdiplus::Graphics* InGraphics)
{
    if (!InGraphics)
    {
        return;
    }
    if (!Image)
    {
        return;
    }
    // Image�� �ε��Ǿ� �ִ�.
    InGraphics->DrawImage(
        Image,                  // �׷��� �̹���
        static_cast<int>(Position.X - Size * Pivot.X),
        static_cast<int>(Position.Y - Size * Pivot.Y),   // �׷��� ��ġ
        Size, Size);  // �׷��� ������
}