#include "Background.h"

Background::Background(const wchar_t* InImagePath)
    :Actor(InImagePath)
{
    Pivot.X = 0;    // ���� ���� �Ǻ�
    Pivot.Y = 0;
}



void Background::OnTick(float InDeltaTime)
{
    Offset += ScrollSpeed * InDeltaTime;
}

void Background::OnRender(Gdiplus::Graphics* InGraphics)
{
    constexpr int PixelGap = 3;
    if (Image)
    {
        // Image�� �ε��Ǿ� �ִ�.
        int NewY = static_cast<int>(Position.Y - Size * Pivot.Y + Offset);
        if (Offset > g_ScreenSize.Y)
        {
            Offset = -static_cast<float>(Size);
        }

        int WidthCount = g_ScreenSize.X / Size + 1;     // +1�� ȭ�� �ۿ� ���� Ÿ���� �׸��� ���� �߰�
        int HeightCount = g_ScreenSize.Y / Size + 2;    // +2�� ȭ�� �ۿ� ���� Ÿ���� �׸��� ���� �߰�
        int TotalHeight = (Size - PixelGap) * HeightCount;

        for(int y = -1; y < HeightCount; y++)
        {
           
            for (int x = 0; x < WidthCount; x++)
            {
                int NewX = static_cast<int>(Position.X - Size * Pivot.X + (Size - PixelGap) * x);
                InGraphics->DrawImage(
                    Image,        // �׷��� �̹���
                    NewX,
                    NewY,         // �׷��� ��ġ
                    Size, Size);  // �׷��� ������
            }
            NewY += (Size - PixelGap);
            if (NewY > TotalHeight)
            {
                NewY -= (TotalHeight + (Size - PixelGap));
            }
        }
       
    }
}