#pragma once
#include "Actor.h"
#include "Enums.h"

// ��� ����� �������̽� ����� �⺻ Ŭ�����Դϴ�. 
class UserInterface : public Actor
{
public:
	UserInterface() = delete;
	UserInterface(ResourceID resourceId) : Actor(resourceId) {};

	inline void SetWidth(int newWidth) { width = newWidth; UpdatePosition(); }
	inline void SetHeight(int newHeight) { height = newHeight; UpdatePosition(); }
	inline void SetPivot(float x, float y) { Pivot.X = x; Pivot.Y = y; UpdatePosition(); }
	inline void SetAnchor(float x, float y) { anchor.X = x; anchor.Y = y; UpdatePosition(); }

protected:
	int width = 0;		// �̹��� ��ü �ʺ�
	int height = 0;		// �̹��� ��ü ����
	PointF anchor = { 0.0f, 0.0f }; // �̹��� ��Ŀ ����Ʈ
	POINT anchoredPosition = { 0, 0 }; // ��Ŀ�� ���������� ��ġ

	void UpdatePosition();
};