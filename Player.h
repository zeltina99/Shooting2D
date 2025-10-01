#pragma once
#include <unordered_map>
#include "enums.h"
#include "Actor.h"

// extern : 뒤에 있는 변수가 다른 파일에 선언이 되어 있다.


class Player : public Actor
{
	/*
		실습  Player 클래스 만들어보기
		①  피봇 위치는 한가운데(float2개)
		②  이미지로 표시
		③  키보드 입력으로 좌우 이동
		④	플레이어가 화면을 벗어나지 않게 하기
	*/

public:
	Player() = delete;
	Player(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.

	virtual void OnTick(float InDeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }

private:

	// 플레이어의 이동 속도
	float Speed = 200.0f;

	// 플레이어 키 입력 상태
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
};

// 실습
// ① 플레이어의 움직임이 좌우로 서로 순환되게 만들기
// ② 흐르는 배경 만들기
// ③ 플레이어의 움직이는 속도가 컴퓨터 성능에 영향이 없으려면 어떻게 해야하는가?