#include "BombSpawner.h"
#include "Factory.h"
#include "Bomb.h"

void BombSpawner::OnInitialize()
{
    SetPosition(0, -100); // ȭ�� �ۿ� ��ġ ����. �߿��Ѱ� �ƴ�.

    timeSinceLastSpawn = 0.0f;
    hasInitialDelayPassed = false;
}

void BombSpawner::OnTick(float deltaTime)
{
    Actor::OnTick(deltaTime); // �θ� Ŭ������ OnTick ȣ��

    // ��� �ð� ������Ʈ
    timeSinceLastSpawn += deltaTime;

    // �ʱ� ���� �ð��� �������� Ȯ��
    if (!hasInitialDelayPassed)
    {
        if (timeSinceLastSpawn > initialDelay)
        {
            hasInitialDelayPassed = true;
            timeSinceLastSpawn = 0.0f; // Ÿ�̸� ����
        }
        return; // �ʱ� ���� �ð��� ������ �ʾ����� ���⼭ ����
    }

    // �ʱ� ���� �ð��� ���� ���� ��ź ���� ����
    if (timeSinceLastSpawn > spawnInterval)
    {
        // ��ź ����
        Bomb* newBomb = Factory::Get().SpawnActor<Bomb>(ResourceID::Bomb, RenderLayer::Bomb);

        // Ÿ�̸� ���� (���� ���� ������ ����)
        timeSinceLastSpawn -= spawnInterval;
    }
}