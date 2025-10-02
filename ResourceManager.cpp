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
    LoadResourceFromFile(ResourceID::Dot, L"./Images/dot.png");
    LoadResourceFromFile(ResourceID::Test, L"./Images/Tile.png");
}
void ResourceManager::Destroy()
{
    for (auto& pair : Resources)
    {
        delete pair.second;  // �ε��� ��Ʈ�� ��� �����
    }
    Resources.clear();
}


Gdiplus::Bitmap* ResourceManager::GetImage(ResourceID InID)
{
    auto iter = Resources.find(InID);   // �����ϰ� ����
    if (iter != Resources.end())
    {
        return iter->second;
    }
    return nullptr;

    //return Resources[InID]; // �̷��� �ص� ū ������ ����.
}


bool ResourceManager::LoadResourceFromFile(ResourceID InID, const wchar_t* path)
{
    bool Result = false;
    if (path)
    {
        Gdiplus::Bitmap* Image = new Gdiplus::Bitmap(path);  //  �̹��� �ε�
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // ���������� ���� �ε��� �ȉ��.
            delete Image;           // ���������� ��� ����
            Image = nullptr;
            OutputDebugString(L"�̹��� �ε� ����");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"�̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
        }
        else
        {
            Resources[InID] = Image;
            Result = true;
        }
    }

    return Result;
    
}

