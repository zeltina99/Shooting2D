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
	// Singleton : 클래스의 인스턴스가 1개만 있는 클래스.
	// private에 생성자를 넣어서 밖에서 인스턴스화 하는 것을 원천적으로 봉쇄
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;	// 복사 생성자 삭제
	ResourceManager& operator=(const ResourceManager&) = delete; // 대입 연산자 삭제
	ResourceManager(const ResourceManager&&) = delete;	// 이동 생성자 삭제
	ResourceManager& operator=(const ResourceManager&&) = delete; // 이동 대입 연산자 삭제

	std::map<BitmapLayer, Gdiplus::Bitmap*> Images;


};


// ② ResourceManager만들기
//      - 싱글톤 클래스
//      - 게임에서 사용될 모든 이미지파일을 관리
//      - 원하는 이미지파일의 Bitmap 리턴
//      - enum class 활용하기