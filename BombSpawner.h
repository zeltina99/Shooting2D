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
	float initialDelay = 2.0f;			// 초기 폭탄 생성 지연 시간
	float spawnInterval = 0.1f;			// 초당 폭탄 생성 간격

	bool hasInitialDelayPassed = false;	// 초기 지연 시간이 지났는지 여부
	float timeSinceLastSpawn = 0.0f;	// 마지막 폭탄 생성 이후 경과 시간

	float ElapsedSinceStart = 0.0f; // 전체 경과 시간
	float GrowthInterval = 10.0f;   // 10초마다 커짐
	float CurrentScale = 1.0f;      // 현재 스케일 배수
};