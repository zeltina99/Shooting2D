#pragma once

class Actor;	// ���漱��
class Component
{
public:
	Component(Actor* InOwner) : Owner(InOwner) {};
	virtual ~Component() = default;

	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void OnTick(float InDeltaTime) {};

	inline Actor* GetOwner() const { return Owner; }

protected:
	Actor* Owner = nullptr;	// �� ������Ʈ�� ����ִ� ����
};