#include "Actor.h"
#include "GameManager.h"
#include "ResourceManager.h"

Actor::Actor(ResourceID InID)
{
    Image = ResourceManager::Get().GetImage(InID);
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