#pragma once

template <typename T>
class Singleton
{
public:
	virtual ~Singleton() = default;
	Singleton(const Singleton&) = delete;	// ���� ������ ����
	Singleton& operator=(const Singleton&) = delete; // ���� ������ ����
	Singleton(const Singleton&&) = delete;	// �̵� ������ ����
	Singleton& operator=(const Singleton&&) = delete; // �̵� ���� ������ 
	

protected:
	Singleton() = default;
public:
	static T* Get()
	{
		static T instance;
		return &instance;
	}

};

