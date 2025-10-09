#include "ResourceManager.h"
#include "GameManager.h"



void ResourceManager::Initialize()
{
    Resources[ResourceID::None] = nullptr;
    LoadResourceFromFile(ResourceID::Player, L"./Images/Airplane.png");
    LoadResourceFromFile(ResourceID::Bomb, L"./Images/Bomb.png");
    LoadResourceFromFile(ResourceID::Background, L"./Images/EffectB.png");
    LoadResourceFromFile(ResourceID::Number0, L"./Images/00.png");
    LoadResourceFromFile(ResourceID::Number1, L"./Images/01.png");
    LoadResourceFromFile(ResourceID::Number2, L"./Images/02.png");
    LoadResourceFromFile(ResourceID::Number3, L"./Images/03.png");
    LoadResourceFromFile(ResourceID::Number4, L"./Images/04.png");
    LoadResourceFromFile(ResourceID::Number5, L"./Images/05.png");
    LoadResourceFromFile(ResourceID::Number6, L"./Images/06.png");
    LoadResourceFromFile(ResourceID::Number7, L"./Images/07.png");
    LoadResourceFromFile(ResourceID::Number8, L"./Images/08.png");
    LoadResourceFromFile(ResourceID::Number9, L"./Images/09.png");
    LoadResourceFromFile(ResourceID::Map1, L"./Images/Map1.png");
    LoadResourceFromFile(ResourceID::Map2, L"./Images/Map2.png");
    LoadResourceFromFile(ResourceID::Map3, L"./Images/Map3.png");
    LoadResourceFromFile(ResourceID::Map4, L"./Images/Map4.png");
    LoadResourceFromFile(ResourceID::Map5, L"./Images/Map5.png");
    LoadResourceFromFile(ResourceID::Map6, L"./Images/Map6.png");
    LoadResourceFromFile(ResourceID::Map7, L"./Images/Map7.png");
    LoadResourceFromFile(ResourceID::Map8, L"./Images/Map8.png");
    LoadResourceFromFile(ResourceID::Map9, L"./Images/Map9.png");
    LoadResourceFromFile(ResourceID::Dot, L"./Images/Dot.png");
    LoadResourceFromFile(ResourceID::Test, L"./Images/Tile.png");
}
void ResourceManager::Destroy()
{
    for (auto& pair : Resources)
    {
        delete pair.second;  // 로드한 비트맵 모두 지우기
    }
    Resources.clear();
}


Gdiplus::Bitmap* ResourceManager::GetImage(ResourceID InID)
{
    auto iter = Resources.find(InID);   // 안전하게 가기
    if (iter != Resources.end())
    {
        return iter->second;
    }
    return nullptr;

    //return Resources[InID]; // 이렇게 해도 큰 문제는 없다.
}


bool ResourceManager::LoadResourceFromFile(ResourceID InID, const wchar_t* path)
{
    bool Result = false;
    if (path)
    {
        Gdiplus::Bitmap* Image = new Gdiplus::Bitmap(path);  //  이미지 로딩
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // 정상적으로 파일 로딩이 안됬다.
            delete Image;           // 실패했으면 즉시 해제
            Image = nullptr;
            OutputDebugString(L"이미지 로드 실패");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
        }
        else
        {
            Resources[InID] = Image;
            Result = true;
        }
    }

    return Result;
    
}

