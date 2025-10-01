#include "ResourceManager.h"

void ResourceManager::Initialize()
{
	Images[BitmapLayer::Background] = new Gdiplus::Bitmap(L"./Images/EffectB.png");
	Images[BitmapLayer::Player] = new Gdiplus::Bitmap(L"./Images/Airplane.png");
}

void ResourceManager::Destroy()
{
    for (auto& pair : Images)
    {
        if (pair.second)
        {
            delete pair.second;
            pair.second = nullptr;
        }
    }
    Images.clear();
}

