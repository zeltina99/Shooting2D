#include "Background.h"
#include "GameManager.h"
#include "ResourceManager.h"

Background::Background(ResourceID InID)
    :Actor(InID)
{
    Pivot.X = 0;    // 왼쪽 위가 피봇
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

    // 1) 타일 포인터 (1회 캐시)
    static Gdiplus::Bitmap* T_Map1 = nullptr; // 30%
    static Gdiplus::Bitmap* T_Map5 = nullptr; // 나머지 70%를 3개로
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

    // 2) 스크롤/그리드
    int NewY = static_cast<int>(Position.Y - Size * Pivot.Y + Offset);
    if (Offset > GameManager::ScreenHeight)
        Offset = -static_cast<float>(Size);

    const int widthCount = GameManager::ScreenWidth / Size + 1;
    const int heightCount = GameManager::ScreenHeight / Size + 2;
    const int strideX = (Size - PixelGap);
    const int strideY = (Size - PixelGap);
    const int totalHeight = strideY * heightCount;

    // 3) Offset 래핑과 무관한 월드 Y 유지 (스크롤해도 타일 선택이 고정되도록)
    static float s_lastOffset = 0.0f;
    static int   s_worldRowBase = 0;
    if (Offset < s_lastOffset) s_worldRowBase += heightCount; // 한 화면만큼 넘어가면 행 시작 증가
    s_lastOffset = Offset;

    // 4) 모듈러 기반 가중치 선택(해시 없음)
    //    - s10 = (3*gx + 7*gy) % 10  -> 0..2 이면 Map1 (정확히 30%)
    //    - 나머지(70%)는 (gx + 2*gy) % 3 으로 5/8/9를 균등 분배
    //    계수(3,7,2)는 눈에 띄는 줄무늬를 줄이기 위한 서로소 조합.
    for (int y = -1; y < heightCount; ++y)
    {
        const int gyWorld = s_worldRowBase + y;
        int NewX = static_cast<int>(Position.X - Size * Pivot.X);

        for (int x = 0; x < widthCount; ++x)
        {
            const int gxWorld = x;

            // 0..9 사이 주기: 3/10 = 30% → Map1
            int s10 = ((3 * gxWorld) + (7 * gyWorld)) % 10;
            if (s10 < 0) s10 += 10;

            Gdiplus::Bitmap* tile = nullptr;
            if (s10 < 3) {
                // 30% 구간
                tile = T_Map1;
            }
            else {
                // 70% 구간: 3-way 균등
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