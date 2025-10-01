#pragma once
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
	~Player();

	virtual void Tick(float InDeltaTime) override;
	virtual void Render(Gdiplus::Graphics* InGraphics) override;
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

private:
	 //�÷��̾ �׷��� ũ��
	static constexpr int PixelSize = 64;

	// �÷��̾��� �߽���
	//PointF Pivot = { 0.5f, 0.5f };	// Pivot �⺻ ���� �Ѱ��

	// �÷��̾��� ��ġ
	//PointF Position = { 0.0f, 0.0f };

	// �÷��̾��� �̵� �ӵ�
	//float Speed = 200.0f;

	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// �÷��̾� �̹����� ������� ��Ʈ��
	//Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����
};

// �ǽ�
// �� �÷��̾��� �������� �¿�� ���� ��ȯ�ǰ� �����
// �� �帣�� ��� �����
// �� �÷��̾��� �����̴� �ӵ��� ��ǻ�� ���ɿ� ������ �������� ��� �ؾ��ϴ°�?