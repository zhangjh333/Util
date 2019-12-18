/************************************************************
Copyright (C), START LIMITED 2019

File name: Template.cpp

Author: zhangjh		Version: 1.0	Date: 2019-08-22 

Description:  编程规范模板

History:

1. Date:
   Author:
   Modification:

*************************************************************/


// 不稳定的头文件在前,或者说我们自己修改的头文件
#include "stdafx.h"
#include "Template.h"

// 稳定的头文件在后,或者说系统头文件
#include <atlbase.h>
#include <sys\stat.h> 

// 全局变量
int g_nTestCont = 0;

//内部函数无需放入头文件，若有顺序问题，向前声明为静态
static int TestTemplete();


/**
 * @brief 函数的规范模板
 * @param strCmdLine [in] - 参数
 * @param bShow [in] - 参数
 * @param pData [in] - 参数
 * @return 返回值
 */
bool StandardTemplete(string strCmdLine, bool bShow, const char *pData)
{
	//参数合法检查
	if (pData == NULL)
	{
		return false;
	}

	// 分段注释
	STARTUPINFO stStartInfo;
	memset(&stStartInfo, 0, sizeof(stStartInfo)); 
	stStartInfo.cb = sizeof(STARTUPINFO);

	// 分段注释
	PROCESS_INFORMATION stProcessInfo;
	memset(&stProcessInfo, 0, sizeof(stProcessInfo)); // 逗号紧跟空格

	DWORD dwCreationFlags = 0;

	// 关键字紧跟空格
	if (bShow)
	{
		//一行一个语句，切忌一行多个语句，无论多少行，请加上大括号
		dwCreationFlags = CREATE_NEW_CONSOLE; 
	}
	else
	{
		dwCreationFlags = CREATE_NO_WINDOW;
	}

	// 代码行过长时，需要换行，以完整表达式的位置换行
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

	// 内部函数
	TestTemplete();

	// 释放句柄
	CloseHandle(stProcessInfo.hProcess);
	CloseHandle(stProcessInfo.hThread); 

	return true;
}


/**
 * @brief  内部函数
 * @return 返回值
 */
static int TestTemplete()
{
	// 错误情况
	if (false)
	{
		return RET_ERR_PARAM; // 宏定义错误码
	}

	return RET_OK;
}