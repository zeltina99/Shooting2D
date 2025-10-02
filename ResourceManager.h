#pragma once
#include <unordered_map>
#include "Common.h"
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

	Gdiplus::Bitmap* GetImage(ResourceID InID);


private:
	// Singleton : Ŭ������ �ν��Ͻ��� 1���� �ִ� Ŭ����.
	// private�� �����ڸ� �־ �ۿ��� �ν��Ͻ�ȭ �ϴ� ���� ��õ������ ����
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;	// ���� ������ ����
	ResourceManager& operator=(const ResourceManager&) = delete; // ���� ������ ����
	ResourceManager(const ResourceManager&&) = delete;	// �̵� ������ ����
	ResourceManager& operator=(const ResourceManager&&) = delete; // �̵� ���� ������ ����

	bool LoadResourceFromFile(ResourceID InID, const wchar_t* path);	// ���Ͽ��� ���ҽ��� �ε��ϴ� �Լ�

	std::unordered_map<ResourceID, Gdiplus::Bitmap*> Resources;	// ��� ���ҽ��� �� ����ִ� ��

};

