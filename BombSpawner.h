#pragma once
#include "Actor.h"

class BombSpawner : public Actor
{
public:
	BombSpawner() = delete;
	BombSpawner(ResourceID resourceId) : Actor(resourceId) {};

	virtual void OnInitialize() override;
	virtual void OnTick(float deltaTime) override;

private:
	float initialDelay = 2.0f;			// �ʱ� ��ź ���� ���� �ð�
	float spawnInterval = 0.1f;			// �ʴ� ��ź ���� ����

	bool hasInitialDelayPassed = false;	// �ʱ� ���� �ð��� �������� ����
	float timeSinceLastSpawn = 0.0f;	// ������ ��ź ���� ���� ��� �ð�

	float ElapsedSinceStart = 0.0f; // ��ü ��� �ð�
	float GrowthInterval = 10.0f;   // 10�ʸ��� Ŀ��
	float CurrentScale = 1.0f;      // ���� ������ ���
};