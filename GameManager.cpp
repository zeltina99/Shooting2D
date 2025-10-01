#include "GameManager.h"
#include "Background.h"
#include "Player.h"
#include "TestGridActor.h"

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

    Background* background = new Background(L"./Images/EffectB.png");
    background->SetRenderLayer(RenderLayer::Background);
    AddActor(background);
    MainPlayer = new Player(L"./Images/Airplane.png");
    MainPlayer->SetRenderLayer(RenderLayer::Player);
    AddActor(MainPlayer);
    TestGridActor* GridActor = new TestGridActor();
    GridActor->SetRenderLayer(RenderLayer::Test);
    AddActor(GridActor);
}

void GameManager::Destroy()
{
    for (Actor* Actor : Actors)
    {
        delete Actor;
    }
    Actors.clear();

    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
   
}

void GameManager::Tick(float InDeltaTime)
{
    for (Actor* Actor : Actors)
    {
        Actor->OnTick(InDeltaTime);
    }
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // BackBufferGraphics �ʼ�
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        std::map<RenderLayer, std::vector<Actor*>> LayeredActors;

        for (Actor* Actor : Actors)
        {
            if (Actor)
            {
                RenderLayer layer = Actor->GetRenderLayer();
                LayeredActors[layer].push_back(Actor);
            }
        }
        for (auto& pair : LayeredActors)
        {
            for (Actor* Actor : pair.second)
            {
                Actor->OnRender(BackBufferGraphics);  // �Ǵ� OnRender
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