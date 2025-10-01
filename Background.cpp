#include "Background.h"

Background::Background(const wchar_t* InImagePath)
{
    Pivot.X = 0;    // ���� ���� �Ǻ�
    Pivot.Y = 0;
    Position.Y = -PixelSize;
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

Background::~Background()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Background::Tick(float InDeltaTime)
{
    Offset += Speed * InDeltaTime;
}

void Background::Render(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        // Image�� �ε��Ǿ� �ִ�.
        int NewY = static_cast<int>(Position.Y - PixelSize * Pivot.Y + Offset);
        if (Offset > g_ScreenSize.Y)
        {
            Offset = -PixelSize;
        }

        int WidthCount = g_ScreenSize.X / PixelSize + 1;
        int HeightCount = g_ScreenSize.Y / PixelSize + 2;
        int TotalHeight = (PixelSize - 3) * HeightCount;

        for(int y = -1; y < HeightCount; y++)
        {
           
            for (int x = 0; x < WidthCount; x++)
            {
                int NewX = static_cast<int>(Position.X - PixelSize * Pivot.X + (PixelSize - 3) * x);
                InGraphics->DrawImage(
                    Image,                  // �׷��� �̹���
                    NewX,
                    NewY,                    // �׷��� ��ġ
                    PixelSize, PixelSize);  // �׷��� ������
            }
            NewY += (PixelSize - 3);
            if (NewY > TotalHeight)
            {
                NewY -= (TotalHeight + (PixelSize - 3));
            }
        }
       
    }
}