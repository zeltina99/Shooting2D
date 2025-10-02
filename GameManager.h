#pragma once
#include <Windows.h>
#include <vector>
#include <set>
#include <map>
#include "Common.h"
#include "Actor.h"
#include "Player.h"
#include "Singleton.h"
#include "TestGridActor.h"

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

	void RegistActor(RenderLayer InLayer, Actor* InActor);
	inline void RequestDestroy(Actor* DestroyTarget) { PendingDestroyActors.push_back(DestroyTarget); }

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

	void UnregisteActor(Actor* InActor);
	void ProcessPendingDestroyActors();			// ���� ������ ���͵��� ������ �����ϴ� �Լ�

	//std::vector<Actor*> Actors;
	std::map<RenderLayer, std::set<Actor*>> Actors;
	std::vector<Actor*> PendingDestroyActors;	// ���� ������ ���͵��� ���

	HWND hMainWindow = nullptr;
	Point AppPosition = Point(100, 100);
	Gdiplus::Bitmap* BackBuffer = nullptr;    // ����ۿ� ����
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // ����ۿ� ���̿� �׸��� ���� ����

	Player* MainPlayer = nullptr;
	TestGridActor* TestGrid = nullptr;
};