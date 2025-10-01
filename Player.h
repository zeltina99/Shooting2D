#pragma once
#include <unordered_map>
#include "enums.h"
#include "Actor.h"

// extern : �ڿ� �ִ� ������ �ٸ� ���Ͽ� ������ �Ǿ� �ִ�.


class Player : public Actor
{
	/*
		�ǽ�  Player Ŭ���� ������
		��  �Ǻ� ��ġ�� �Ѱ��(float2��)
		��  �̹����� ǥ��
		��  Ű���� �Է����� �¿� �̵�
		��	�÷��̾ ȭ���� ����� �ʰ� �ϱ�
	*/

public:
	Player() = delete;
	Player(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.

	virtual void OnTick(float InDeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }

private:

	// �÷��̾��� �̵� �ӵ�
	float Speed = 200.0f;

	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
};

// �ǽ�
// �� TestActor����� -> 50�ȼ� ������ ���� ��ġ Ȯ�� ���� �� �� �ְ� ���ִ� Ŭ����
// �� TestHouseActor����� -> ����� �׷��ִ� Ŭ����