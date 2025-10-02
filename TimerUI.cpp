#include "TimerUI.h"
#include "ResourceManager.h"
#include "GameManager.h"

void TimerUI::OnInitialize()
{
	Actor::OnInitialize();	// �θ� Ŭ������ OnInitialize ȣ��

	SetSize(GameManager::ActorDefaultSize / 2);	// ũ�� ����
	anchoredPosition = { -10, 10 };			// ��Ŀ�� ���������� ��ġ ����
	anchor = { 1.0f, 0.0f };				// ��Ŀ ����Ʈ�� ������ ������� ����
	Pivot = { 1.0f, 0.0f };					// �Ǻ� ����Ʈ�� ������ ������� ����
	width = Size * 4;
	height = Size;							// ��ü �ʺ�� 4�ڸ�(0.00) * size, ���̴� size�� ����
	UpdatePosition();

	digits.reserve(3);			// �ּ� 3�� �ڸ� ���ڸ� ������ �� �ֵ��� ���� ����(0.00)
	digitImages.reserve(10);	// 0���� 9������ ���� �̹��� ����
	// 0���� 9������ ���� �̹��� �ε�
	for (int i = 0; i < 10; ++i)
	{
		digitImages.push_back(ResourceManager::Get().GetImage(static_cast<ResourceID>(static_cast<int>(ResourceID::Number0) + i)));
	}
	dotImage = ResourceManager::Get().GetImage(ResourceID::Dot); // �Ҽ��� �̹��� �ε�
}

void TimerUI::OnTick(float deltaTime)
{
	Actor::OnTick(deltaTime);
	elapsedTime += deltaTime; // ��� �ð� ������Ʈ
	SetNumber(elapsedTime); // ��ǥ ���ڸ� ����. 
}

void TimerUI::OnRender(Gdiplus::Graphics* graphics)
{
	if (!graphics) return;

	int digitCount = static_cast<int>(digits.size());
	int indexOffset = digitCount;
	for (int i = 0; i < digitCount; ++i)
	{
		if (i == 2)
		{
			// �Ҽ��� �׸���
			graphics->DrawImage(dotImage, static_cast<int>(Position.X) + indexOffset * Size, static_cast<int>(Position.Y), Size, Size);
			indexOffset--;
		}

		RenderDigit(graphics, digits[i], indexOffset); // �� �ڸ� ���� ������. digits���� �ڸ����� ������ ����Ǿ� �����Ƿ�, ���� ���� �ڸ����� ������
		indexOffset--;
	}
}

void TimerUI::SetNumber(float number)
{
	if (targetNumber != number)
	{
		targetNumber = number; // ��ǥ ���� ������Ʈ

		digits.clear(); // ������ ����� ���� ����
		int number = static_cast<int>(targetNumber * 100.0f); // �Ҽ��� ��° �ڸ����� ���. �� �Ʒ��� ���� ó��
		do
		{
			digits.push_back(number % 10);	// ���� �ڸ� ���ڸ� �߰�
			number /= 10;					// ���� �ڸ��� �̵�
		} while (number > 0);	// ��� �ڸ� ���ڸ� ó���� ������ �ݺ�(targetNumber�� ���ۺ��� 0�� ��츦 ����� do-while���)

		// �ּ� 0.00����� �Ǿ�� �Ѵ�.
		const int minimumDigits = 3; // �ּ� 3�ڸ� ����(0.00) ����
		int paddingCount = minimumDigits - (int)digits.size();
		for (int i = 0; i < paddingCount; ++i)
		{
			digits.push_back(0);	// ������ �ڸ����� 0���� ä��
		}

		SetWidth(Size * (static_cast<int>(digits.size()) + 1)); // �ʺ�� size * (�ڸ��� + �Ҽ��� �ڸ�)
	}
}

void TimerUI::RenderDigit(Gdiplus::Graphics* graphics, int digit, unsigned int index)
{
	if (digit < 0 || digit > 9)
	{
		return; // ��ȿ���� ���� �ε����� ���� ó��
	}

	// �Ǻ��� ���� ������� ����
	graphics->DrawImage(digitImages[digit], static_cast<int>(Position.X) + index * Size, static_cast<int>(Position.Y), Size, Size);
}