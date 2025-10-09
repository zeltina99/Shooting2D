#include "Bomb.h"
#include "GameManager.h"
#include "PhysicsComponent.h"
//#include <string>

void Bomb::OnInitialize()
{
	dropSpeed = 0.0f; // �ʱ� ��� �ӵ� ����

	SetSize(GameManager::ActorDefaultSize / 2); // ũ�� ����

	float HalfSize = Size * 0.5f;
	Position.X = static_cast<float>(HalfSize + rand() % (GameManager::ScreenWidth - Size)); // ���� X ��ġ ����
	Position.Y = static_cast<float>(-Size); // ȭ�� ���ʿ��� ����

	//std::string debugMessage = "Bomb::position.X : " + std::to_string(position.X) + "\n";
	//OutputDebugStringA(debugMessage.c_str());

	Angle = 180.0f;	// ȸ�� ����

	PhysicsComponent* physicsComponent = new PhysicsComponent(this, CollisionType::Rectangle, PhysicsLayer::Bomb);
	physicsComponent->SetWidth(static_cast<float>(HalfSize));
	physicsComponent->SetHeight(HalfSize * 0.75f);
	AddComponent(physicsComponent); // ���� ������Ʈ �߰�
}

void Bomb::OnTick(float deltaTime)
{
	Actor::OnTick(deltaTime); // �θ� Ŭ������ OnTick ȣ��

	dropSpeed += dropAcceleration * deltaTime; // ��� �ӵ� ������Ʈ
	//std::string debugMessage = "Bomb::OnTick called with deltaTime: " + std::to_string(dropSpeed) + "\n";
	//OutputDebugStringA(debugMessage.c_str());

	Position.Y += dropSpeed * deltaTime; // Y ��ġ ������Ʈ

	lifetime -= deltaTime; // ���� ����

	// ȭ�� ������ �����ų� ������ �� �� ��� ���� ����
	if (Position.Y > GameManager::ScreenHeight + Size || lifetime < 0.0f)
	{
		DestroyActor();
	}
}

void Bomb::OnOverlap(Actor* other)
{
	if (other && other != this)
	{
		// ��ź�� �ٸ� ���Ͱ� ��ĥ �� ó��
		// ��: ��ź�� �÷��̾�� ��ġ�� �÷��̾�� ���ظ� �ְų� ���� ���� ó��
		OutputDebugString(L"Bomb::OnOverlap called\n");

		// ��ź ����
		DestroyActor();
	}
}

void Bomb::Rescale(float scale)
{
	// Bomb�� �⺻ ������� OnInitialize���� ActorDefaultSize / 2 �� ��� �����Ƿ�,
   // �� ���ؿ� ���� �������� ���Ѵ�.
	int newSize = static_cast<int>((GameManager::ActorDefaultSize * 0.5f) * scale);
	SetSize(newSize);

	// �浹 ������Ʈ�� �� ũ�⿡ ���� ����
	if (auto* physicsComponent = GetComponent<PhysicsComponent>())
	{
		float half = newSize * 0.5f;
		physicsComponent->SetWidth(half);
		physicsComponent->SetHeight(half * 0.75f);
	}
}
