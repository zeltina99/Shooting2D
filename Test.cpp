#include "Test.h"

void Test::TestActor(Gdiplus::Graphics* InBuffer,Gdiplus::SolidBrush& InBrush)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 12; x++)
        {
            InBuffer->FillRectangle(&InBrush, 50 * x, 50 * y, 5, 5);
        }
    }
}

void Test::TestHouseActor()
{
    Gdiplus::Point Positions[g_HouseVerticesCount];
    for (int i = 0; i < g_HouseVerticesCount; i++)
    {
        Positions[i] = g_HousePosition + g_HouseVertices[i];
    }
    g_BackBufferGraphics->DrawPolygon(&GreenPen, Positions, g_HouseVerticesCount);
}
