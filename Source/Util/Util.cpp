/************************************************************
Copyright (C), START LIMITED 2019

File name: Util.cpp

Author: zhangjh		Version: 1.0	Date: 2019-08-13 

Description:  整理了平常用到的部分通用接口，后期可追加接口

History:

1. Date:
   Author:
   Modification:

*************************************************************/

//头文件包含遵循不稳定的在前
#include "stdafx.h"
#include "Util.h"

#include <stdio.h>
#include <malloc.h>
#include <ctime>
#include <direct.h>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>


// 内部函数声明
static string GetFileDirectory(string strFilePath);


/**
 * @brief 获取注册表子键的字符串值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @return 字符串的键值
 */
string GetRegistryInfo(HKEY hKey, string strRegPath, string strName)
{
	CRegKey obReg;
	string strKey = _T("");

	// 打开注册表项
	if (obReg.Open(hKey, strRegPath.c_str(), KEY_READ) == ERROR_SUCCESS)
	{
		long nRet = 0;
		char szKeyBuf[MAX_PATH * 4];
		unsigned long nBufSize = MAX_PATH * 4;

		// 获取表项的值
		nRet = obReg.QueryStringValue(strName.c_str(), szKeyBuf, &nBufSize);

		if (nRet == ERROR_SUCCESS)
		{
			strKey = szKeyBuf;
		}

		// 关闭释放
		obReg.Close();
	}

	return strKey;
}

/**
 * @brief 获取注册表子键的整形值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @return 整形的键值
 */
DWORD GetRegistryValue(HKEY hKey, string strRegPath, string strName)
{
	CRegKey obReg;
	DWORD dwKey = 0;

	// 打开注册表项
	if (obReg.Open(hKey, strRegPath.c_str(), KEY_READ) == ERROR_SUCCESS)
	{
		// 获取表项的值
		if (obReg.QueryDWORDValue(strName.c_str(), dwKey) == ERROR_SUCCESS)
		{
			// do nothing!
		}

		obReg.Close();
	}

	return dwKey;
}

/**
 * @brief 设置注册表子键的字符串值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @param strName [in] - 子键的字符串值
 * @return 成功ture，失败false
 */
bool SetRegistryInfo(HKEY hkey, string strRegPath, string strName, string strValue)
{
	CRegKey obReg;
	bool bSuccess = false;

	// 打开注册表项
	if (obReg.Open(hkey, strRegPath.c_str(), KEY_WRITE) == ERROR_SUCCESS)
	{
		long nRet = 0;

		// 设置表项的值
		nRet = obReg.SetStringValue(strName.c_str(), strValue.c_str(), REG_SZ);
		
		if (nRet == ERROR_SUCCESS)
		{
			bSuccess = true;

			obReg.Flush();
		}

		obReg.Close();
	}

	return bSuccess;
}

/**
 * @brief 设置注册表子键的整形值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @param strName [in] - 子键的整形值
 * @return 成功ture，失败false
 */
bool SetRegistryValue(HKEY hkey, string strRegPath, string strName, DWORD dwValue)
{
	CRegKey obReg;
	bool bSuccess = false;

	// 打开注册表项
	if (obReg.Open(hkey, strRegPath.c_str(), KEY_WRITE) == ERROR_SUCCESS)
	{
		// 设置表项的值
		if (obReg.SetDWORDValue(strName.c_str(), dwValue) == ERROR_SUCCESS)
		{
			bSuccess = true;

			obReg.Flush();
		}

		obReg.Close();
	}

	return bSuccess;
}

/**
 * @brief  执行一个可执行的文件
 * @param strFileName [in] - 本地文件的名称
 * @param strParam [in] - 传入的参数
 * @param bShow [in] - 是否显示界面
 * @param bWait [in] - 是否等待程序退出
 * @return 成功ture，失败false
 */
bool Execute(string strFilePath, string strParam, bool bShow, bool bWait)
{
	SHELLEXECUTEINFO stSeiInfo;


	//可执行文件结构参数
	stSeiInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	stSeiInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	stSeiInfo.hwnd = NULL;
	stSeiInfo.lpVerb = "open";

	stSeiInfo.lpFile = strFilePath.c_str();
	stSeiInfo.lpParameters = strParam.c_str();
	stSeiInfo.lpDirectory = NULL;

	stSeiInfo.hInstApp = NULL;

	//是否显示界面
	if(bShow)
	{
		stSeiInfo.nShow = SW_SHOWNORMAL;
	}
	else
	{
		stSeiInfo.nShow = SW_HIDE;
	}

	//执行程序
	if(!::ShellExecuteEx(&stSeiInfo))
	{
		return false;
	}
	
	//等待执行完毕
	if(bWait)
	{
		::WaitForSingleObject(stSeiInfo.hProcess, INFINITE);
	}
	

	// 释放句柄
	CloseHandle(stSeiInfo.hProcess);

	return true;
}

/**
 * @brief  执行命令行
 * @param strCmdLine [in] - 命令行
 * @param bShow [in] - 是否显示界面
 * @param bWait [in] - 是否等待执行完毕
 * @return 成功ture，失败false
 */
bool Execute(string strCmdLine, bool bShow, bool bWait)
{
	//窗体结构体信息
	STARTUPINFO stStartInfo;
	memset(&stStartInfo, 0, sizeof(stStartInfo));
	stStartInfo.cb = sizeof(STARTUPINFO);

	//进程信息
	PROCESS_INFORMATION stProcessInfo;
	memset(&stProcessInfo, 0, sizeof(stProcessInfo));

	DWORD dwCreationFlags = 0;

	//是否显示窗口
	if (bShow)
	{
		dwCreationFlags = CREATE_NEW_CONSOLE;
	}
	else
	{
		dwCreationFlags = CREATE_NO_WINDOW;
	}

	//创建进程
	if (!::CreateProcess(NULL, (LPTSTR) strCmdLine.c_str(), NULL, NULL
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
	
	//等待进程退出
	if (bWait)
	{
		::WaitForSingleObject(stProcessInfo.hProcess, INFINITE);
	}
	
	// 释放句柄
	CloseHandle(stProcessInfo.hProcess);
	CloseHandle(stProcessInfo.hThread); 

	return true;
}

/**
 * @brief 获取当前工作路径
 * @return 工作路径
 */
string GetWorkingDirectory()
{
	char szBuffer[MAX_PATH] = "";

	// 获取当前工作路径
	_getcwd(szBuffer, MAX_PATH);

	return string(szBuffer);
}

/**
 * @brief 获取当前程序的绝对路径
 * @return 绝对路径
 */
string GetProgramDirectory()
{
	string strProgramDir = "";
	
	char szFilePath[MAX_PATH] = "";

	// 获取当前程序的绝对路径
	if(::GetModuleFileNameA(NULL, szFilePath, MAX_PATH) != 0)
	{
		strProgramDir = GetFileDirectory(string(szFilePath));
	}

	return strProgramDir;
}

/**
 * @brief 查找替换字符串
 * @param strSource [in] - 源字符串
 * @param strFind [in] - 要查找的字符串
 * @param strReplace [in] - 替换的字符串
 * @return 替换的次数
 */	
long FindReplace(string &strSource, string strFind, string strReplace)
{
	long nCount = 0;

	string::size_type nPos = 0;

	// 查找到字符串，并替换
	while (string::npos != (nPos = strSource.find(strFind, nPos)))
	{
		strSource.replace(nPos, strFind.size(), strReplace);
		nPos += strReplace.size();

		nCount++;
	}

	// 返回替换的次数
	return nCount;
}

/**
 * @brief 字符串去除空格
 * @param strSource [in] - 源字符串
 * @param strReplace [in] - 被替换的串
 * @return 无
 */
void RemoveWhiteSpaces(string &strSource, string strReplace)
{
	//替换空格、tab、换行符
	FindReplace(strSource, " ", strReplace);
	FindReplace(strSource, "\t", strReplace);
	FindReplace(strSource, "\r", strReplace);
	FindReplace(strSource, "\n", strReplace);
}

/**
 * @brief 去除左右空格、换行
 * @param strSource [in] - 源字符串
 * @param strTrim [in] - 要去除的串
 * @param bLeft [in] - 是否去除左
 * @param bRight [in] - 是否去除右
 * @return 无
 */
void Trim(string &strSource, string strTrim, bool bLeft, bool bRight)
{
	// 第一个不是空格的位置
	size_t nStartIndex = strSource.find_first_not_of(strTrim);

	if (nStartIndex == string::npos)
	{
		return; // 没找到
	}

	size_t nEndIndex = 0;

	// 去除左空格
	if (bLeft)
	{
		nEndIndex = strSource.size() - nStartIndex;
		
		strSource = strSource.substr(nStartIndex, nEndIndex);
	}

	// 去除右空格
	if (bRight)
	{
		nEndIndex = strSource.find_last_not_of(strTrim) + 1;

		strSource = strSource.substr(0, nEndIndex);
	}

}

/**
 * @brief 获取分割符的个数
 * @param strSource [in] - 源字符串
 * @param strSource [in] - 分隔符
 * @return 分割符的个数
 */
long GetTokenCount(string strSource, string strDelimiter)
{
	//参数合法性判断
	if(strSource.compare("") == 0)
	{
		return 0;
	}

	long nIndex = 0;
	long nTokenCount = 0;

	while (true)
	{
		//查找分割符
		nIndex = (long) strSource.find(strDelimiter, nIndex);

		if(nIndex >= 0)
		{
			nTokenCount++; //找到，机器数累加
			nIndex++; 
		}
		else
		{
			break;
		}
	}

	return nTokenCount;
}

/**
 * @brief 根据分隔符顺序截取字符串
 * @param strSource [in] - 源字符串
 * @param strSource [in] - 分隔符
 * @param nTokenIndex [in] - 分隔符序号
 * @return 截取的字符串
 */
string GetToken(string strSource, string strDelimiter, long nTokenIndex)
{
	//参数合法性判断
	if(strSource.compare("") == 0 || nTokenIndex < 0)
	{
		return string("");
	}

	string strText = strSource;
	long nDelimiterLength = (long) strDelimiter.size();

	while (true)
	{
		long nIndex = 0;
		string strTemp = "";

		// 查找分割符的位置
		nIndex = (long) strText.find(strDelimiter, nIndex);

		if(nIndex >= 0)
		{
			//截取分割符之间的字符串
			strTemp = strText.substr(0, nIndex);
		}
		else
		{
			strTemp = strText;
		}

		//删除已经找过的字符
		strText.erase(0, nIndex + nDelimiterLength);

		nTokenIndex--;

		if(nTokenIndex < 0)
		{
			return strTemp;
		}
	}
}

/**
 * @brief 字符串转成大写
 * @param str [in] - 要转化的字符串
 * @return 已转化的字符串
 */	
string ToUpper(string str)
{
	string strUpper = str;
	std::transform(strUpper.begin(), strUpper.end(), strUpper.begin(), toupper);
	return strUpper;
}

/**
 * @brief 字符串转成小写
 * @param str [in] - 要转化的字符串
 * @return 已转化的字符串
 */	
string ToLower(string str)
{
	string strLower = str;
	std::transform(strLower.begin(), strLower.end(), strLower.begin(), tolower);
	return strLower;
}

/**
 * @brief 不区分大小写比较
 * @param str1 [in] - 要对比的字符串
 * @param str2 [in] - 要对比的字符串
 * @return 0 不等，1相等
 */
int CompareNoCase(string str1, string str2)
{
	// 转成大写做比较
	return !ToUpper(str1).compare(ToUpper(str2));
}

/**
 * @brief 本地文件根据偏移位置载入缓冲区
 * @param strFilePath [in] - 本地文件路径
 * @param nFileSize [in] - 本地文件大小
 * @param nStart [in] - 开始偏移位置
 * @param nEnd [in] - 结束偏移位置
 * @return 文件的缓冲区数据
 */
char* GetFileContent(string strFilePath, long &nFileSize, long nStart, long nEnd)
{
	// 参数合法校验
	if (strFilePath.compare("") == 0)
	{
		return NULL;
	}
	
	// 打开文件，等同fopen_s
	FILE* pFileInput = _fsopen(strFilePath.c_str(), "rb", _SH_DENYNO);
	if (pFileInput == NULL)
	{
		return NULL;
	}

	// 获取文件大小
	fseek(pFileInput, 0, SEEK_END);
	
	nFileSize = ftell(pFileInput);
	rewind(pFileInput);

	if (nFileSize <= 0)
	{
		fclose(pFileInput); // 关闭文件句柄

		return NULL;
	}

	// 检查数据有效性
	if (nEnd >= (nFileSize - 1))
	{
		nEnd = nFileSize - 1;
	}

	long nReadNumber = 0;

	// 获取所需要的内存大小
	if (nStart == 0 && nEnd == 0)
	{
		nReadNumber = nFileSize;
	}
	else if (nEnd < nFileSize && nStart <= nEnd)
	{
		nReadNumber = nEnd - nStart + 1;

		// 文件偏移到开始位置
		fseek(pFileInput, nStart, SEEK_SET);
	}
	else
	{
		fclose(pFileInput); //关闭文件句柄

		return NULL;
	}

	// 分配堆空间 - 由调用者释放
	char* pFileContent = new char[nReadNumber];

	if (pFileContent == NULL)
	{
		fclose(pFileInput);

		return NULL;
	}

	// 拷贝文件内容
	fread(pFileContent, sizeof(char), nReadNumber, pFileInput);

	// 关闭文件句柄
	fclose(pFileInput);

	// 返回文件缓冲区
	return pFileContent;
}

/**
 * @brief 缓冲区数据写入文件
 * @param strFilePath [in] - 本地文件路径
 * @param nFileSize [in] - 缓冲区大小
 * @param pFileContent [in] - 缓冲区数据
 * @return 成功失败
 */
bool SetFileContent(string strFilePath, const char *pFileContent, long &nFileSize)
{
	// 参数合法校验
	if (strFilePath.compare("") == 0 
		|| pFileContent == NULL
		|| nFileSize <= 0)
	{
		return false;
	}

	// 打开文件，等同fopen_s
	FILE* pFileOutput = _fsopen(strFilePath.c_str(), "wb", _SH_DENYWR);

	if (pFileOutput == NULL)
	{
		return false;
	}

	// 缓冲区数据写入文件
	nFileSize = fwrite(pFileContent, sizeof(char), nFileSize, pFileOutput);

	// 释放文件句柄
	fclose(pFileOutput);

	return true;
}

/**
 * @brief 缓冲区数据追加到文件
 * @param strFilePath [in] - 本地文件路径
 * @param nFileSize [in] - 缓冲区大小
 * @param pFileContent [in] - 缓冲区数据
 * @return 成功失败
 */
bool AppendFileContent(string strFilePath, const char *pFileContent, long &nFileSize)
{
	// 参数合法校验
	if (strFilePath.compare("") == 0 
		|| pFileContent == NULL
		|| nFileSize <= 0)
	{
		return false;
	}

	// 打开文件，等同fopen_s
	FILE* pFileOutput = _fsopen(strFilePath.c_str(), "ab", _SH_DENYWR);

	if (pFileOutput == NULL)
	{
		return false;
	}

	// 数据追加写入文件
	nFileSize = fwrite(pFileContent, sizeof(char), nFileSize, pFileOutput);

	// 释放句柄
	fclose(pFileOutput);

	return true;
}

/**
 * @brief 获取本地文件大小
 * @param strFilePath [in] - 本地文件路径
 * @return 文件大小
 */
long GetFileSize(string strFilePath)
{
	long nFileSize = 0;

	//获取文件大小
	nFileSize = (long) GetFileSize64(strFilePath);
	if (nFileSize > 0)
	{
		return nFileSize;
	}

	// 如果以上方式失败，尝试旧方式获取
	FILE* pFile = _fsopen(strFilePath.c_str(), "rb", _SH_DENYNO);
		
	if (pFile == NULL)
	{
		return -1; // 文件不存在
	}
	
	// 获取文件大小
	fseek(pFile, 0, SEEK_END);

	nFileSize = ftell(pFile);
	rewind(pFile);

	// 关闭文件句柄
	fclose(pFile);

	return nFileSize;
	
}

/**
 * @brief 获取本地文件大小
 * @param strFilePath [in] - 本地文件路径
 * @return 文件大小
 */
__int64 GetFileSize64(string strFilePath)
{ 
	struct __stat64 stFileStat;
	
	//获取文件的信息
	if (_stat64(strFilePath.c_str(), &stFileStat) != 0)
	{
		return -1;
	}

	return stFileStat.st_size;
}

/**
 * @brief 是否是文件
 * @param strFileName [in] - 本地文件路径
 * @return 是或不是
 */
bool IsFile(string strFilePath)
{
	std::ifstream ifsFile(strFilePath.c_str());

	//为空，表示非文件
	return (ifsFile != NULL);
}

/**
 * @brief 取整，四舍五入
 * @param dNumber2Round [in] - 小数值
 * @return 整形值
 */
long Round(double dNumber2Round)
{
	double dResult = dNumber2Round;

	if (dResult < 0)
	{
		dResult -= 0.5;
	}
	else
	{
		dResult += 0.5;
	}

	return (long) dResult;
}

/**
 * @brief 是否偶数
 * @param nNumber [in] -  数字
 * @return 是 ture，否 false
 */
bool IsPowerOf2(unsigned long nNumber)
{
	return ((nNumber & (nNumber - 1)) == 0);
}
/**
 * @brief 整形转字符串
 * @param nNumber [in] - 整形值
 * @return 字符串
 */
string Long2String(long nNumber)
{
	std::ostringstream strStream;
	strStream << nNumber;

	return strStream.str();
}

/**
 * @brief 小数转字符串
 * @param dNumber [in] - 小数值
 * @param nPrecision [in] - 精度
 * @return 字符串
 */
string Double2String(double dNumber, long nPrecision)
{
	std::ostringstream strStream;
	
	if (nPrecision <= 0)
	{
		strStream << dNumber;
	}
	else
	{
		strStream << std::fixed;
		strStream << std::setprecision(nPrecision) << dNumber;
	}

	return strStream.str();
}


/**
 * @brief 获取系统时间
 * @param strDateFormat [in] - 时间格式
 * @return 系统时间，字符串
 */
string GetSystemTime(time_t& ttTime, string strDateFormat)
{
	string strTime = "";
	tm tmTime;

	if (localtime_s(&tmTime, &ttTime) == 0)
	{
		char strBuffer[MAX_PATH];

		strftime(strBuffer, sizeof(strBuffer), strDateFormat.c_str(), &tmTime);

		strTime = strBuffer;
	}

	return strTime;
}

/**
 * @brief 获取系统时间
 * @param strDateFormat [in] - 时间格式
 * @return 系统时间，字符串
 */
string GetSystemTime(string strDateFormat)
{
	time_t ttCurrentTime = 0;
	time(&ttCurrentTime);

	return GetSystemTime(ttCurrentTime, strDateFormat);
}

/**
 * @brief 秒转换成时分秒
 * @param strTime [in] -  秒数
 * @return 时分秒
 */
string GetTime(long lSeconds)
{
	char strBuffer[16];

	sprintf_s(strBuffer, 16, "%02d:%02d:%02d\0", lSeconds / 3600
		, (lSeconds % 3600) / 60 
		, lSeconds % 60
		);

	return string(strBuffer);
}

/**
 * @brief 时分秒转化成秒
 * @param strTime [in] - 时间
 * @return 秒数
 */
long GetTime(string strTime)
{
	if (GetTokenCount(strTime, ":") != 2)
	{
		return 0;
	}

	long lHour = atol(GetToken(strTime, ":", 0).c_str());
	long lMinute = atol(GetToken(strTime, ":", 1).c_str());
	long lSecond = atol(GetToken(strTime, ":", 2).c_str());

	return ((lHour * 60 * 60) + (lMinute * 60) + lSecond);
}

//内部接口
string AddDirectoryEnding(string strDirPath)
{
	if (strDirPath.compare("") == 0)
	{
		return string("");
	}

	string strDir = strDirPath;

	if (strDir[strDir.size() - 1] != DIRECTORY_SEPARATOR_C)
	{
		strDir += DIRECTORY_SEPARATOR;
	}

	return strDir;
}


//内部接口
string RemoveDirectoryEnding(string strDirPath)
{
	if (strDirPath.compare("") == 0)
	{
		return string("");
	}

	string strDir = strDirPath;

	if (strDir[strDir.size() - 1] == DIRECTORY_SEPARATOR_C)
	{
		strDir.erase(strDir.size() - 1);
	}

	return strDir;
}

//内部接口
string GetFileDirectory(string strFilePath)
{
	if (strFilePath.compare("") == 0)
	{
		return string("");
	}

	string strDir = RemoveDirectoryEnding(strFilePath);

	size_t nIndex = strDir.find_last_of(DIRECTORY_SEPARATOR);

	if (nIndex == string::npos)
	{
		return string("");
	}

	strDir.erase(nIndex);

	return strDir;
}

//内部接口
string GetDirectoryName(string strDirPath)
{
	if (strDirPath.compare("") == 0)
	{
		return string("");
	}

	string strDirName = RemoveDirectoryEnding(strDirPath);

	size_t nIndex = strDirName.find_last_of(DIRECTORY_SEPARATOR);

	if (nIndex == string::npos)
	{
		return string("");
	}

	strDirName.erase(0, nIndex + 1);

	return strDirName;
}

/**
 * @brief 创建文件夹，包含子文件夹
 * @param strDirPath [in] - 目录路径
 * @return 无
 */

void MakeDirectory(string strDirPath)
{
	// 参数合法校验
	if (strDirPath.compare(_T("")) == 0)
	{
		return;
	}

	string strDirPathCopy = RemoveDirectoryEnding(strDirPath);

	// 获取斜杆的个数
	long nCount = GetTokenCount(strDirPathCopy, DIRECTORY_SEPARATOR);

	// 截取目录名
	string strDir = GetToken(strDirPathCopy, DIRECTORY_SEPARATOR, 0);

	long nIndex = 0;

	// 循环依次创建子目录
	for (nIndex = 1; nIndex < nCount; nIndex++)
	{
		strDir += DIRECTORY_SEPARATOR;
		strDir += GetToken(strDirPathCopy, DIRECTORY_SEPARATOR, nIndex);

		CreateDirectory(strDir.c_str(), NULL);
		SetFileAttributes(strDir.c_str(), FILE_ATTRIBUTE_NORMAL);
	}

}

/**
 * @brief 删除文件夹，包含子文件夹
 * @param strDirPath [in] - 目录路径
 * @return 文件绝对路径
 */
void DeleteDirectory(string strDirPath)
{
	// 参数合法验证
	if (strDirPath.compare(_T("")) == 0)
	{
		return;
	}

	// 去除末尾的斜杆'\'
	string strCurrDir = RemoveDirectoryEnding(strDirPath);

	// 拼装查找路径字符串
	string strDesPath;
	strDesPath += "\\\\?\\";
	strDesPath += strCurrDir;
	strDesPath = AddDirectoryEnding(strDesPath);
	strDesPath += "*.*";

	// 要删除的路径
	string strDelDir;
	strDelDir += "\\\\?\\";
	strDelDir += strCurrDir;

	WIN32_FIND_DATA stDesktop = {0};

	HANDLE hDesktop = ::FindFirstFile(strDesPath.c_str(), &stDesktop);	

	// 查找失败，表示文件夹为空
	if (hDesktop == INVALID_HANDLE_VALUE)
	{
		// 删除文件夹
		RemoveDirectory(strDelDir.c_str());

		return;
	}

	do 
	{
		// 构造路径
		string strPath = _T("");
		strPath += strCurrDir;
		strPath = AddDirectoryEnding(strPath);
		strPath += stDesktop.cFileName;

		// 是否找到文件夹
		if (stDesktop.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// 获取目录名称
			string strCurrDirName = GetDirectoryName(strPath);

			if (strCurrDirName == "." || strCurrDirName == "..")
			{
				continue;
			}
			else
			{
				// 递归删除
				DeleteDirectory(strPath);
			}
		}
		else 
		{
			//找到文件，删除文件
			_tunlink(strPath.c_str());
		}
	}
	while (::FindNextFile(hDesktop, &stDesktop) == TRUE);

	// 关闭句柄
	::FindClose(hDesktop);

	// 删除文件夹
	RemoveDirectory(strDelDir.c_str());
}



