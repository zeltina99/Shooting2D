#include "Player.h"
#include "Common.h"
#include "GameManager.h"

Player::Player(ResourceID InID)
    : Actor(InID)
{
    Position.X = 300.0f;
    Position.Y = 700.0f;
    KeyWasPressedMap[InputDirection::Up] = false;
    KeyWasPressedMap[InputDirection::Down] = false;
    KeyWasPressedMap[InputDirection::Left] = false;
    KeyWasPressedMap[InputDirection::Right] = false; 

    PhysicsComponent* physicsComponent = new PhysicsComponent(this, CollisionType::Circle, PhysicsLayer::Player);
    physicsComponent->SetRadius(static_cast<float>(Size * 0.5f)); // ������ ����
    AddComponent(physicsComponent); // ���� ������Ʈ �߰�
}


void Player::OnTick(float InDeltaTime)
{
    float MoveDistance = InDeltaTime * Speed;
    if (KeyWasPressedMap[InputDirection::Left])
    {
        Position.X -= MoveDistance;
    }
    if (KeyWasPressedMap[InputDirection::Right])
    {
        Position.X += MoveDistance;
    }

    if (Position.X < (0 - Size * 0.5f))
    {
        Position.X = GameManager::ScreenWidth + Size * 0.5f; // ��ȯ �̵�
    }
    else if ((GameManager::ScreenWidth + Size * 0.5f) < Position.X)
    {
        Position.X = static_cast<float>(0 - Size * 0.5f);
    }
}

void Player::OnRender(Gdiplus::Graphics* InGraphics)
{
    Actor::OnRender(InGraphics);    // �θ��� OnRender ����
    
    // �θ��� OnRender ������ �� �߰��� ���� ����
    if (!Image)    
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            static_cast<int>(Position.X - Size * Pivot.X),    // �׷��� ��ġ
            static_cast<int>(Position.Y - Size * Pivot.Y),
            Size, Size);
    }
}

void Player::OnOverlap(Actor* InOther)
{
    OutputDebugString(L"Player::OnOverlap called\n");
    if (InOther && InOther != this)
    {
        // ���� ���� ó��
        GameManager::Get().SetGameState(GameState::GameOver);
    }
}

void Player::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    if (InKey == VK_LEFT || InKey == VK_RIGHT)
    {
        KeyWasPressedMap[static_cast<InputDirection>(InKey)] = InIsPressed;
    }
}