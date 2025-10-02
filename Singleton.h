#pragma once

template <typename T>
class Singleton
{
public:
	static T& Get()
	{
		static T instance;
		return instance;
	}

protected:
	// Singleton : Ŭ������ �ν��Ͻ��� 1���� �ִ� Ŭ����.
	// private/protected�� �����ڸ� �־ �ۿ��� �ν��Ͻ�ȭ �ϴ� ���� ��õ������ ����
	Singleton() = default;
	virtual ~Singleton() = default;

	Singleton(const Singleton&) = delete;				// ���� ������ ����
	Singleton& operator=(const Singleton&) = delete;	// ���� ������ ����
	Singleton(const Singleton&&) = delete;				// �̵� ������ ����
	Singleton& operator=(const Singleton&&) = delete;	// �̵� ���� ������ ����

	// Rule of Five
	// �ټ����� �׸� �� �ϳ��� ���� ���������� ������ �װ����� ���� �����ϰų� ��������� = default, = delete �ؾ��Ѵ�.
	// �� �Ҹ���, �� ���� ������, �� ���� ������, �� �̵� ������, �� �̵� ���� ������
};