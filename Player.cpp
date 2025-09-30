#include "Player.h"

void Player::LoadImage(HWND hWnd)
{
    image = Gdiplus::Bitmap::FromFile(L"./Images/Airplane.png");
    if (!image || image->GetLastStatus() != Gdiplus::Ok)
    {
        MessageBox(hWnd, L"이미지 로드 실패", L"오류", MB_OK);
        delete image;
        image = nullptr;
    }
}

void Player::ReleaseImage()
{
    delete image;
    image = nullptr;
}

void Player::Draw(Gdiplus::Graphics* graphics)
{
    if (image)
    {
        constexpr int width = 64;
        constexpr int height = 64;

        int drawX = position.X - width / 2;
        int drawY = position.Y - height / 2;

        graphics->DrawImage(image, drawX, drawY, width, height);
    }
}

void Player::Move(int dx, int dy)
{
    if ((position.X >= 32) && (position.X <= 768))
    {
        position.X += dx;
    }
    else if (position.X > 768)
    {
        position.X = 768;
    }
    else if (position.X < 32)
    {
        position.X = 32;
    }
    
    if ((position.Y >= 0) && (position.Y <= 600))
    {
        position.Y += dy;
    }
    else if (position.Y > 600)
    {
        position.Y = 600;
    }
    else
    {
        position.Y = 0;
    }
}
