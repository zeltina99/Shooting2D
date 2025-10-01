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
        // 혹시 안만들어졌을 때를 대비한 에러 출력
        MessageBox(hMainWindow, L"백 버퍼 그래픽스 생성 실패", L"오류", MB_OK | MB_ICONERROR);
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
    if (BackBufferGraphics)   // BackBufferGraphics 필수
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
                Actor->OnRender(BackBufferGraphics);  // 또는 OnRender
            }
        }
    }
   
  
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}

// 실습
// ① RenderLayer 순서에 따라 그리도록 GameManager 수정하기
// ② ResourceManager만들기
//      - 싱글톤 클래스
//      - 게임에서 사용될 모든 이미지파일을 관리
//      - 원하는 이미지파일의 Bitmap 리턴
//      - enum class 활용하기