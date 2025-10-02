#pragma once
#include "UserInterface.h"
#include <vector>

class TimerUI : public UserInterface
{
public:
	TimerUI() = delete;
	TimerUI(ResourceID resourceId) : UserInterface(resourceId) {};

	virtual void OnInitialize() override;
	virtual void OnTick(float deltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* graphics) override;

private:
	void SetNumber(float number);
	void RenderDigit(Gdiplus::Graphics* graphics, int digit, unsigned int index);

	float targetNumber = 0.0f;	// ��ǥ ����
	float elapsedTime = 0.0f;	// ��� �ð�
	std::vector<int> digits;	// �� �ڸ� ���ڸ� �����ϴ� ����(0.0�� �� �־�� �ϹǷ� �ּ� 2�� �ڸ��� ����)
	std::vector<Gdiplus::Bitmap*> digitImages;	// �� �ڸ� ���� �̹���
	Gdiplus::Bitmap* dotImage = nullptr;		// �Ҽ��� �̹���

};