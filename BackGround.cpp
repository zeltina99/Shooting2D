#include "BackGround.h"


BackGround::BackGround(const wchar_t* InImagePath)
{
    Position.X = 0;
    Position.Y = 0;

    BGImage = new Gdiplus::Bitmap(InImagePath);  // �÷��̾� �̹��� �ε�
    if (BGImage->GetLastStatus() != Gdiplus::Ok)
    {
        // ���������� ���� �ε��� �ȉ��.
        delete BGImage;           // ���������� ��� ����
        BGImage = nullptr;
        OutputDebugString(L"�÷��̾� �̹��� �ε� ����");
        MessageBox(g_hMainWindow, L"�÷��̾� �̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
    }
}

BackGround::~BackGround()
{
    if (BGImage)
    {
        delete BGImage;
        BGImage = nullptr;
    }
}

void BackGround::BackRender(Gdiplus::Graphics* Graphics)
{
    if (!BGImage) 
    {
        return;
    }

    const int ImgWidth = BGImage->GetWidth();
    const int ImgHeight = BGImage->GetHeight();

    // ȭ�� ��ü�� Ÿ��ó�� ä��
    for (int y = -ImgHeight; y < g_ScreenSize.Y; y += ImgHeight)
    {
        for (int x = 0; x < g_ScreenSize.X; x += ImgWidth)
        {
            int drawY = y + OffsetY;
            Graphics->DrawImage(BGImage, x, drawY, ImgWidth, ImgHeight);
        }
    }

    // ��ũ�� �̵�
    OffsetY = (OffsetY + ScrollSpeed) % ImgHeight;
}

