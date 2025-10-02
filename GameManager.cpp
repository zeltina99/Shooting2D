#include "GameManager.h"
#include "Background.h"
#include "Player.h"
#include "TestGridActor.h"
#include "ResourceManager.h"

void GameManager::Initialize()
{
    BackBuffer = new Gdiplus::Bitmap(
        GameManager::ScreenWidth, GameManager::ScreenHeight, PixelFormat32bppARGB);
    BackBufferGraphics = Gdiplus::Graphics::FromImage(BackBuffer);
    if (!BackBufferGraphics)
    {
        // Ȥ�� �ȸ�������� ���� ����� ���� ���
        MessageBox(hMainWindow, L"�� ���� �׷��Ƚ� ���� ����", L"����", MB_OK | MB_ICONERROR);
    }

    Background* background = new Background(ResourceID::Background);
    background->SetRenderLayer(RenderLayer::Background);
    MainPlayer = new Player(ResourceID::Player);
    AddActor(RenderLayer::Player, MainPlayer);
    AddActor(RenderLayer::Background, background);
    AddActor(RenderLayer::Test, new TestGridActor());
}

void GameManager::Destroy()
{
    for (auto pair : Actors)
    {
        for(Actor* actor : pair.second)
        {
            delete actor;
        }
        pair.second.clear();
    }
    Actors.clear();

    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
   
}

void GameManager::Tick(float InDeltaTime)
{
    for (const auto& pair : Actors)
    {
        for (Actor* actor : pair.second)
        {
            actor->OnTick(InDeltaTime);
        }
    }
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // g_BackBufferGraphics �ʼ�
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        for (const auto& pair : Actors)
        {
            for (Actor* actor : pair.second)
            {
                actor->OnRender(BackBufferGraphics);
            }
        }

    }
  
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}

// �ǽ�
// �� RenderLayer ������ ���� �׸����� GameManager �����ϱ�
// �� ResourceManager�����
//      - �̱��� Ŭ����
//      - ���ӿ��� ���� ��� �̹��������� ����
//      - ���ϴ� �̹��������� Bitmap ����
//      - enum class Ȱ���ϱ�