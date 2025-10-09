#include "Background.h"
#include "GameManager.h"
#include "ResourceManager.h"

Background::Background(ResourceID InID)
    :Actor(InID)
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
    if (!InGraphics) return;

    // 1) Ÿ�� ������ (1ȸ ĳ��)
    static Gdiplus::Bitmap* T_Map1 = nullptr; // 30%
    static Gdiplus::Bitmap* T_Map5 = nullptr; // ������ 70%�� 3����
    static Gdiplus::Bitmap* T_Map8 = nullptr;
    static Gdiplus::Bitmap* T_Map9 = nullptr;
    static bool s_inited = false;
    if (!s_inited) {
        auto& RM = ResourceManager::Get();
        T_Map1 = RM.GetImage(ResourceID::Map1);
        T_Map5 = RM.GetImage(ResourceID::Map5);
        T_Map8 = RM.GetImage(ResourceID::Map8);
        T_Map9 = RM.GetImage(ResourceID::Map9);
        s_inited = true;
    }
    if (!T_Map1 || !T_Map5 || !T_Map8 || !T_Map9) return;

    // 2) ��ũ��/�׸���
    int NewY = static_cast<int>(Position.Y - Size * Pivot.Y + Offset);
    if (Offset > GameManager::ScreenHeight)
        Offset = -static_cast<float>(Size);

    const int widthCount = GameManager::ScreenWidth / Size + 1;
    const int heightCount = GameManager::ScreenHeight / Size + 2;
    const int strideX = (Size - PixelGap);
    const int strideY = (Size - PixelGap);
    const int totalHeight = strideY * heightCount;

    // 3) Offset ���ΰ� ������ ���� Y ���� (��ũ���ص� Ÿ�� ������ �����ǵ���)
    static float s_lastOffset = 0.0f;
    static int   s_worldRowBase = 0;
    if (Offset < s_lastOffset) s_worldRowBase += heightCount; // �� ȭ�鸸ŭ �Ѿ�� �� ���� ����
    s_lastOffset = Offset;

    // 4) ��ⷯ ��� ����ġ ����(�ؽ� ����)
    //    - s10 = (3*gx + 7*gy) % 10  -> 0..2 �̸� Map1 (��Ȯ�� 30%)
    //    - ������(70%)�� (gx + 2*gy) % 3 ���� 5/8/9�� �յ� �й�
    //    ���(3,7,2)�� ���� ��� �ٹ��̸� ���̱� ���� ���μ� ����.
    for (int y = -1; y < heightCount; ++y)
    {
        const int gyWorld = s_worldRowBase + y;
        int NewX = static_cast<int>(Position.X - Size * Pivot.X);

        for (int x = 0; x < widthCount; ++x)
        {
            const int gxWorld = x;

            // 0..9 ���� �ֱ�: 3/10 = 30% �� Map1
            int s10 = ((3 * gxWorld) + (7 * gyWorld)) % 10;
            if (s10 < 0) s10 += 10;

            Gdiplus::Bitmap* tile = nullptr;
            if (s10 < 3) {
                // 30% ����
                tile = T_Map1;
            }
            else {
                // 70% ����: 3-way �յ�
                int s3 = (gxWorld + 2 * gyWorld) % 3;
                if (s3 < 0) s3 += 3;
                switch (s3) {
                case 0: tile = T_Map5; break;
                case 1: tile = T_Map8; break;
                default: tile = T_Map9; break; // case 2
                }
            }

            if (tile)
                InGraphics->DrawImage(tile, NewX, NewY, Size, Size);

            NewX += strideX;
        }

        NewY += strideY;
        if (NewY > totalHeight)
            NewY -= (totalHeight + strideY);
    }
}