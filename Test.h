#pragma once
#include "Actor.h"

class Test : public Actor
{
public:
	void TestActor(Gdiplus::Graphics* InBuffer, Gdiplus::SolidBrush& InBrush);
	void TestHouseActor();

protected:

};

// 실습
// ① TestActor만들기 -> 50픽셀 단위로 점찍어서 위치 확인 쉽게 할 수 있게 해주는 클래스
// ② TestHouseActor만들기 -> 집모양 그려주는 클래스