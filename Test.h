#pragma once
#include "Actor.h"

class Test : public Actor
{
public:
	void TestActor(Gdiplus::Graphics* InBuffer, Gdiplus::SolidBrush& InBrush);
	void TestHouseActor();

protected:

};

// �ǽ�
// �� TestActor����� -> 50�ȼ� ������ ���� ��ġ Ȯ�� ���� �� �� �ְ� ���ִ� Ŭ����
// �� TestHouseActor����� -> ����� �׷��ִ� Ŭ����