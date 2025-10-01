#include "Background.h"

Background::Background(const wchar_t* InImagePath) : Actor(InImagePath)
{

    SetSpeed(50.0f);

    SetPivot({ 0,0 });
   
    Position.Y = -PixelSize;
    
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
        // Image가 로딩되어 있다.
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
                    Image,                  // 그려질 이미지
                    NewX,
                    NewY,                    // 그려질 위치
                    PixelSize, PixelSize);  // 그려질 사이즈
            }
            NewY += (PixelSize - 3);
            if (NewY > TotalHeight)
            {
                NewY -= (TotalHeight + (PixelSize - 3));
            }
        }
       
    }
}