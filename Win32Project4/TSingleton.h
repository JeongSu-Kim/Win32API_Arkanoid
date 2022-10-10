#pragma once
#include "stdafx.h"

template <typename T>
class TSingleton
{
private:

	friend T;

	static T* m_pInstance;

private:
	TSingleton() {}

public:
	virtual ~TSingleton()
	{
		/*if (m_pInstance != NULL)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}*/
	}
	static T* GetInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new T;
			//m_pInstance->Init();
		}

		return m_pInstance;
	}
};

template <typename T>
T* TSingleton<T>::m_pInstance = NULL;