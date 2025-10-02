#include "Actor.h"
#include "GameManager.h"
#include "ResourceManager.h"

Actor::Actor(ResourceID InID)
{
    Image = ResourceManager::Get().GetImage(InID);
}

void Actor::DestroyActor()
{
    if (!IsPendingDestroy)
    {
        IsPendingDestroy = true;
        GameManager::Get().RequestDestroy(this);    // �ڽ��� ���� ��û�ϱ�
    }
}

void Actor::OnTick(float InDeltaTime)
{
}

void Actor::OnRender(Gdiplus::Graphics* InGraphics)
{
    if (!InGraphics) return;
    if (!Image) return;

    //// ���� ��ȯ ���� ����
    //Gdiplus::Matrix oldTransform;
    //InGraphics->GetTransform(&oldTransform);

    //// ȸ�� �߽����� ��ü�� �߽����� ����
    //InGraphics->TranslateTransform(Position.X, Position.Y);

    //// ������ ������ŭ ȸ��
    //InGraphics->RotateTransform(Angle);

    // Image�� �ε��Ǿ� �ִ�.
    InGraphics->DrawImage(
        Image,          // �׷��� �̹���
        static_cast<int>(Position.X - Size * Pivot.X),    // �׷��� ��ġ
        static_cast<int>(Position.Y - Size * Pivot.Y),
        Size, Size);  // �׷��� ������

    //// ���� ��ȯ ���·� ����
    //InGraphics->SetTransform(&oldTransform);
}

void Actor::AddComponent(Component* InComponent)
{
    if (InComponent)
    {
        Components.push_back(InComponent);
        InComponent->OnInitialize(); // ������Ʈ �ʱ�ȭ ȣ��
    }
}

void Actor::RemoveComponent(Component* InComponent)
{
    if (InComponent)
    {
        auto it = std::find(Components.begin(), Components.end(), InComponent);
        if (it != Components.end())
        {
            (*it)->OnDestroy(); // ������Ʈ �ı� ȣ��

            std::swap(*it, Components.back());
            Components.pop_back();   // ���� �� �� ������� ������Ʈ ����
            delete InComponent;
            InComponent = nullptr;
        }
    }
}