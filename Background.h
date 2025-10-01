#pragma once
#include "Common.h"
#include "Actor.h"

class Background : public Actor
{
public:
	Background() = delete;
	Background(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.

	virtual void OnTick(float InDeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

private:
	
	// ��ũ�� �ӵ�
	float ScrollSpeed = 50.0f;
	
	// ��ũ�� ������ ��
	float Offset = 0.0f;
};

