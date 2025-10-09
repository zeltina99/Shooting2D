#include "BombSpawner.h"
#include "Factory.h"
#include "Bomb.h"

void BombSpawner::OnInitialize()
{
    SetPosition(0, -100); // ȭ�� �ۿ� ��ġ ����. �߿��Ѱ� �ƴ�.

    timeSinceLastSpawn = 0.0f;
    hasInitialDelayPassed = false;

    ElapsedSinceStart = 0.0f;
    CurrentScale = 1.0f;
}

void BombSpawner::OnTick(float deltaTime)
{
    Actor::OnTick(deltaTime); // �θ� Ŭ������ OnTick ȣ��

    // ��� �ð� ������Ʈ
    timeSinceLastSpawn += deltaTime;
    ElapsedSinceStart += deltaTime;

    // === 10�ʸ��� ��ź ũ�� 1.5�辿 ���� ===
    if (ElapsedSinceStart >= GrowthInterval)
    {
        ElapsedSinceStart -= GrowthInterval;
        CurrentScale *= 1.5f; // ũ�� 1.5�� ����
    }

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
        // Ÿ�̸� ���� (���� ���� ������ ����)
        timeSinceLastSpawn -= spawnInterval;

        // ��ź ����
        Bomb* newBomb = Factory::Get().SpawnActor<Bomb>(ResourceID::Bomb, RenderLayer::Bomb);

        if (newBomb)
        {
            newBomb->Rescale(CurrentScale);
        }
    }
}