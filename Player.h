#pragma once
#include "framework.h"

class Player
{
public:

    void LoadImage(HWND hWnd);  // �̹��� �ε�
    void ReleaseImage();        // �̹��� ����
    void Draw(Gdiplus::Graphics* graphics);  // �׸���
    void Move(int dx, int dy);  // ��ġ �̵�

private:
    
    
    Gdiplus::Bitmap* image = nullptr;
    Gdiplus::Point position{ 400, 500 };  // �ʱ� ��ġ
    

};

/*
  �ǽ�  Player Ŭ���� ������
      ��  �Ǻ� ��ġ�� �Ѱ��
      ��  �̹����� ǥ��
      ��  Ű���� �Է����� �¿� �̵�
      ��  �÷��̾ ȭ���� ����� �ʰ� �ϱ�
*/