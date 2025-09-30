#pragma once
#include "framework.h"

class Player
{
public:

    void LoadImage(HWND hWnd);  // 이미지 로딩
    void ReleaseImage();        // 이미지 해제
    void Draw(Gdiplus::Graphics* graphics);  // 그리기
    void Move(int dx, int dy);  // 위치 이동

private:
    
    
    Gdiplus::Bitmap* image = nullptr;
    Gdiplus::Point position{ 400, 500 };  // 초기 위치
    

};

/*
  실습  Player 클래스 만들어보기
      ①  피봇 위치는 한가운데
      ②  이미지로 표시
      ③  키보드 입력으로 좌우 이동
      ④  플레이어가 화면을 벗어나지 않게 하기
*/