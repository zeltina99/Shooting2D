#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include "Common.h"
#include "Actor.h"
#include "Player.h"


class ResourceManager
{
public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}
	void Initialize();
	void Destroy();

	// Getter
	Gdiplus::Bitmap* GetBitMap(BitmapLayer Layer)
	{
		auto Iter = Images.find(Layer);
		if (Iter != Images.end())
		{
			return Iter->second;
		}
		return nullptr;
	}



	// Setter



protected:

private:
	// Singleton : Ŭ������ �ν��Ͻ��� 1���� �ִ� Ŭ����.
	// private�� �����ڸ� �־ �ۿ��� �ν��Ͻ�ȭ �ϴ� ���� ��õ������ ����
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;	// ���� ������ ����
	ResourceManager& operator=(const ResourceManager&) = delete; // ���� ������ ����
	ResourceManager(const ResourceManager&&) = delete;	// �̵� ������ ����
	ResourceManager& operator=(const ResourceManager&&) = delete; // �̵� ���� ������ ����

	std::map<BitmapLayer, Gdiplus::Bitmap*> Images;


};


// �� ResourceManager�����
//      - �̱��� Ŭ����
//      - ���ӿ��� ���� ��� �̹��������� ����
//      - ���ϴ� �̹��������� Bitmap ����
//      - enum class Ȱ���ϱ�