/************************************************************
Copyright (C), START LIMITED 2019

File name: Template.cpp

Author: zhangjh		Version: 1.0	Date: 2019-08-22 

Description:  ��̹淶ģ��

History:

1. Date:
   Author:
   Modification:

*************************************************************/


// ���ȶ���ͷ�ļ���ǰ,����˵�����Լ��޸ĵ�ͷ�ļ�
#include "stdafx.h"
#include "Template.h"

// �ȶ���ͷ�ļ��ں�,����˵ϵͳͷ�ļ�
#include <atlbase.h>
#include <sys\stat.h> 

// ȫ�ֱ���
int g_nTestCont = 0;

//�ڲ������������ͷ�ļ�������˳�����⣬��ǰ����Ϊ��̬
static int TestTemplete();


/**
 * @brief �����Ĺ淶ģ��
 * @param strCmdLine [in] - ����
 * @param bShow [in] - ����
 * @param pData [in] - ����
 * @return ����ֵ
 */
bool StandardTemplete(string strCmdLine, bool bShow, const char *pData)
{
	//�����Ϸ����
	if (pData == NULL)
	{
		return false;
	}

	// �ֶ�ע��
	STARTUPINFO stStartInfo;
	memset(&stStartInfo, 0, sizeof(stStartInfo)); 
	stStartInfo.cb = sizeof(STARTUPINFO);

	// �ֶ�ע��
	PROCESS_INFORMATION stProcessInfo;
	memset(&stProcessInfo, 0, sizeof(stProcessInfo)); // ���Ž����ո�

	DWORD dwCreationFlags = 0;

	// �ؼ��ֽ����ո�
	if (bShow)
	{
		//һ��һ����䣬�м�һ�ж����䣬���۶����У�����ϴ�����
		dwCreationFlags = CREATE_NEW_CONSOLE; 
	}
	else
	{
		dwCreationFlags = CREATE_NO_WINDOW;
	}

	// �����й���ʱ����Ҫ���У����������ʽ��λ�û���
	if (!::CreateProcess(NULL, (LPTSTR)strCmdLine.c_str(), NULL, NULL
		, TRUE
		, dwCreationFlags
		, NULL
		, NULL
		, &stStartInfo
		, &stProcessInfo)
		)
	{
		return false;
	}

	// �ڲ�����
	TestTemplete();

	// �ͷž��
	CloseHandle(stProcessInfo.hProcess);
	CloseHandle(stProcessInfo.hThread); 

	return true;
}


/**
 * @brief  �ڲ�����
 * @return ����ֵ
 */
static int TestTemplete()
{
	// �������
	if (false)
	{
		return RET_ERR_PARAM; // �궨�������
	}

	return RET_OK;
}