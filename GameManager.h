#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include "Common.h"
#include "Actor.h"
#include "Player.h"
#include "Singleton.h"

// ���ӳ� ��� ���͸� �������� Ŭ����
class GameManager : public Singleton<GameManager>
{
	// friend : �ٸ� Ŭ������ �ڽ��� private/protected �׸� �����ϴ� ���� ������ش�.
	// Singleton<GameManager>�� GameManager�� private�� ���� ����������.
	friend class Singleton<GameManager>;

public:
	void Initialize();
	void Destroy();
	void Tick(float InDeltaTime);
	void Render();
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	void AddActor(RenderLayer InRenderLayer, Actor* InActor) { Actors[InRenderLayer].push_back(InActor); }

	static constexpr unsigned int ScreenWidth = 600;
	static constexpr unsigned int ScreenHeight = 800;
	static constexpr unsigned int ActorDefaultSize = 64;

	// Getter
	inline const HWND GetMainWindowHandle() const { return hMainWindow; }
	inline const Point& GetAppPosition() const { return AppPosition; }
	inline Gdiplus::Bitmap* GetBackBuffer() const { return BackBuffer; }

	// Setter
	inline void SetMainWindowHandle(HWND InWindowHandle) {
		if (hMainWindow == nullptr)
		{
			hMainWindow = InWindowHandle;	// �� �ѹ��� ������ �� �ִ� ����
		}
	}
protected:
private:
	// Singleton : Ŭ������ �ν��Ͻ��� 1���� �ִ� Ŭ����.
	// private�� �����ڸ� �־ �ۿ��� �ν��Ͻ�ȭ �ϴ� ���� ��õ������ ����
	GameManager() = default;
	virtual ~GameManager() = default;

	//std::vector<Actor*> Actors;
	std::map<RenderLayer, std::vector<Actor*>> Actors;

	HWND hMainWindow = nullptr;
	Point AppPosition = Point(100, 100);
	Gdiplus::Bitmap* BackBuffer = nullptr;    // ����ۿ� ����
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // ����ۿ� ���̿� �׸��� ���� ����

	Player* MainPlayer = nullptr;
};