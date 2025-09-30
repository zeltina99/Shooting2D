#pragma once
#include <unordered_map>
#include <windows.h>
#include <gdiplus.h>
#include "enums.h"

// extern : �ڿ� �ִ� ������ �ٸ� ���Ͽ� ������ �Ǿ� �ִ�.
extern HWND g_hMainWindow;	// g_hMainWindow�� �ٸ� ���Ͽ� �ִٴ� ���� �˷���

class Player
{
	/*
		�ǽ�  Player Ŭ���� ������
		��  �Ǻ� ��ġ�� �Ѱ��
		��  �̹����� ǥ��
		��  Ű���� �Է����� �¿� �̵�
		��	�÷��̾ ȭ���� ����� �ʰ� �ϱ�
	*/

public:
	Player() = delete;
	Player(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
	~Player();

	void Render(Gdiplus::Graphics* InGraphics);

	void HandleKeyState(WPARAM InKey, bool InIsPressed);

private:
	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// �÷��̾� �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����

	// �÷��̾ �׷��� ũ��
	static constexpr int PixelSize = 64;
};

