/************************************************************
Copyright (C), START LIMITED 2019

File name: Util.cpp

Author: zhangjh		Version: 1.0	Date: 2019-08-13 

Description:  ������ƽ���õ��Ĳ���ͨ�ýӿڣ����ڿ�׷�ӽӿ�

History:

1. Date:
   Author:
   Modification:

*************************************************************/

//ͷ�ļ�������ѭ���ȶ�����ǰ
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


// �ڲ���������
static string GetFileDirectory(string strFilePath);


/**
 * @brief ��ȡע����Ӽ����ַ���ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @return �ַ����ļ�ֵ
 */
string GetRegistryInfo(HKEY hKey, string strRegPath, string strName)
{
	CRegKey obReg;
	string strKey = _T("");

	// ��ע�����
	if (obReg.Open(hKey, strRegPath.c_str(), KEY_READ) == ERROR_SUCCESS)
	{
		long nRet = 0;
		char szKeyBuf[MAX_PATH * 4];
		unsigned long nBufSize = MAX_PATH * 4;

		// ��ȡ�����ֵ
		nRet = obReg.QueryStringValue(strName.c_str(), szKeyBuf, &nBufSize);

		if (nRet == ERROR_SUCCESS)
		{
			strKey = szKeyBuf;
		}

		// �ر��ͷ�
		obReg.Close();
	}

	return strKey;
}

/**
 * @brief ��ȡע����Ӽ�������ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @return ���εļ�ֵ
 */
DWORD GetRegistryValue(HKEY hKey, string strRegPath, string strName)
{
	CRegKey obReg;
	DWORD dwKey = 0;

	// ��ע�����
	if (obReg.Open(hKey, strRegPath.c_str(), KEY_READ) == ERROR_SUCCESS)
	{
		// ��ȡ�����ֵ
		if (obReg.QueryDWORDValue(strName.c_str(), dwKey) == ERROR_SUCCESS)
		{
			// do nothing!
		}

		obReg.Close();
	}

	return dwKey;
}

/**
 * @brief ����ע����Ӽ����ַ���ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @param strName [in] - �Ӽ����ַ���ֵ
 * @return �ɹ�ture��ʧ��false
 */
bool SetRegistryInfo(HKEY hkey, string strRegPath, string strName, string strValue)
{
	CRegKey obReg;
	bool bSuccess = false;

	// ��ע�����
	if (obReg.Open(hkey, strRegPath.c_str(), KEY_WRITE) == ERROR_SUCCESS)
	{
		long nRet = 0;

		// ���ñ����ֵ
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
 * @brief ����ע����Ӽ�������ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @param strName [in] - �Ӽ�������ֵ
 * @return �ɹ�ture��ʧ��false
 */
bool SetRegistryValue(HKEY hkey, string strRegPath, string strName, DWORD dwValue)
{
	CRegKey obReg;
	bool bSuccess = false;

	// ��ע�����
	if (obReg.Open(hkey, strRegPath.c_str(), KEY_WRITE) == ERROR_SUCCESS)
	{
		// ���ñ����ֵ
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
 * @brief  ִ��һ����ִ�е��ļ�
 * @param strFileName [in] - �����ļ�������
 * @param strParam [in] - ����Ĳ���
 * @param bShow [in] - �Ƿ���ʾ����
 * @param bWait [in] - �Ƿ�ȴ������˳�
 * @return �ɹ�ture��ʧ��false
 */
bool Execute(string strFilePath, string strParam, bool bShow, bool bWait)
{
	SHELLEXECUTEINFO stSeiInfo;


	//��ִ���ļ��ṹ����
	stSeiInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	stSeiInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	stSeiInfo.hwnd = NULL;
	stSeiInfo.lpVerb = "open";

	stSeiInfo.lpFile = strFilePath.c_str();
	stSeiInfo.lpParameters = strParam.c_str();
	stSeiInfo.lpDirectory = NULL;

	stSeiInfo.hInstApp = NULL;

	//�Ƿ���ʾ����
	if(bShow)
	{
		stSeiInfo.nShow = SW_SHOWNORMAL;
	}
	else
	{
		stSeiInfo.nShow = SW_HIDE;
	}

	//ִ�г���
	if(!::ShellExecuteEx(&stSeiInfo))
	{
		return false;
	}
	
	//�ȴ�ִ�����
	if(bWait)
	{
		::WaitForSingleObject(stSeiInfo.hProcess, INFINITE);
	}
	

	// �ͷž��
	CloseHandle(stSeiInfo.hProcess);

	return true;
}

/**
 * @brief  ִ��������
 * @param strCmdLine [in] - ������
 * @param bShow [in] - �Ƿ���ʾ����
 * @param bWait [in] - �Ƿ�ȴ�ִ�����
 * @return �ɹ�ture��ʧ��false
 */
bool Execute(string strCmdLine, bool bShow, bool bWait)
{
	//����ṹ����Ϣ
	STARTUPINFO stStartInfo;
	memset(&stStartInfo, 0, sizeof(stStartInfo));
	stStartInfo.cb = sizeof(STARTUPINFO);

	//������Ϣ
	PROCESS_INFORMATION stProcessInfo;
	memset(&stProcessInfo, 0, sizeof(stProcessInfo));

	DWORD dwCreationFlags = 0;

	//�Ƿ���ʾ����
	if (bShow)
	{
		dwCreationFlags = CREATE_NEW_CONSOLE;
	}
	else
	{
		dwCreationFlags = CREATE_NO_WINDOW;
	}

	//��������
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
	
	//�ȴ������˳�
	if (bWait)
	{
		::WaitForSingleObject(stProcessInfo.hProcess, INFINITE);
	}
	
	// �ͷž��
	CloseHandle(stProcessInfo.hProcess);
	CloseHandle(stProcessInfo.hThread); 

	return true;
}

/**
 * @brief ��ȡ��ǰ����·��
 * @return ����·��
 */
string GetWorkingDirectory()
{
	char szBuffer[MAX_PATH] = "";

	// ��ȡ��ǰ����·��
	_getcwd(szBuffer, MAX_PATH);

	return string(szBuffer);
}

/**
 * @brief ��ȡ��ǰ����ľ���·��
 * @return ����·��
 */
string GetProgramDirectory()
{
	string strProgramDir = "";
	
	char szFilePath[MAX_PATH] = "";

	// ��ȡ��ǰ����ľ���·��
	if(::GetModuleFileNameA(NULL, szFilePath, MAX_PATH) != 0)
	{
		strProgramDir = GetFileDirectory(string(szFilePath));
	}

	return strProgramDir;
}

/**
 * @brief �����滻�ַ���
 * @param strSource [in] - Դ�ַ���
 * @param strFind [in] - Ҫ���ҵ��ַ���
 * @param strReplace [in] - �滻���ַ���
 * @return �滻�Ĵ���
 */	
long FindReplace(string &strSource, string strFind, string strReplace)
{
	long nCount = 0;

	string::size_type nPos = 0;

	// ���ҵ��ַ��������滻
	while (string::npos != (nPos = strSource.find(strFind, nPos)))
	{
		strSource.replace(nPos, strFind.size(), strReplace);
		nPos += strReplace.size();

		nCount++;
	}

	// �����滻�Ĵ���
	return nCount;
}

/**
 * @brief �ַ���ȥ���ո�
 * @param strSource [in] - Դ�ַ���
 * @param strReplace [in] - ���滻�Ĵ�
 * @return ��
 */
void RemoveWhiteSpaces(string &strSource, string strReplace)
{
	//�滻�ո�tab�����з�
	FindReplace(strSource, " ", strReplace);
	FindReplace(strSource, "\t", strReplace);
	FindReplace(strSource, "\r", strReplace);
	FindReplace(strSource, "\n", strReplace);
}

/**
 * @brief ȥ�����ҿո񡢻���
 * @param strSource [in] - Դ�ַ���
 * @param strTrim [in] - Ҫȥ���Ĵ�
 * @param bLeft [in] - �Ƿ�ȥ����
 * @param bRight [in] - �Ƿ�ȥ����
 * @return ��
 */
void Trim(string &strSource, string strTrim, bool bLeft, bool bRight)
{
	// ��һ�����ǿո��λ��
	size_t nStartIndex = strSource.find_first_not_of(strTrim);

	if (nStartIndex == string::npos)
	{
		return; // û�ҵ�
	}

	size_t nEndIndex = 0;

	// ȥ����ո�
	if (bLeft)
	{
		nEndIndex = strSource.size() - nStartIndex;
		
		strSource = strSource.substr(nStartIndex, nEndIndex);
	}

	// ȥ���ҿո�
	if (bRight)
	{
		nEndIndex = strSource.find_last_not_of(strTrim) + 1;

		strSource = strSource.substr(0, nEndIndex);
	}

}

/**
 * @brief ��ȡ�ָ���ĸ���
 * @param strSource [in] - Դ�ַ���
 * @param strSource [in] - �ָ���
 * @return �ָ���ĸ���
 */
long GetTokenCount(string strSource, string strDelimiter)
{
	//�����Ϸ����ж�
	if(strSource.compare("") == 0)
	{
		return 0;
	}

	long nIndex = 0;
	long nTokenCount = 0;

	while (true)
	{
		//���ҷָ��
		nIndex = (long) strSource.find(strDelimiter, nIndex);

		if(nIndex >= 0)
		{
			nTokenCount++; //�ҵ����������ۼ�
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
 * @brief ���ݷָ���˳���ȡ�ַ���
 * @param strSource [in] - Դ�ַ���
 * @param strSource [in] - �ָ���
 * @param nTokenIndex [in] - �ָ������
 * @return ��ȡ���ַ���
 */
string GetToken(string strSource, string strDelimiter, long nTokenIndex)
{
	//�����Ϸ����ж�
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

		// ���ҷָ����λ��
		nIndex = (long) strText.find(strDelimiter, nIndex);

		if(nIndex >= 0)
		{
			//��ȡ�ָ��֮����ַ���
			strTemp = strText.substr(0, nIndex);
		}
		else
		{
			strTemp = strText;
		}

		//ɾ���Ѿ��ҹ����ַ�
		strText.erase(0, nIndex + nDelimiterLength);

		nTokenIndex--;

		if(nTokenIndex < 0)
		{
			return strTemp;
		}
	}
}

/**
 * @brief �ַ���ת�ɴ�д
 * @param str [in] - Ҫת�����ַ���
 * @return ��ת�����ַ���
 */	
string ToUpper(string str)
{
	string strUpper = str;
	std::transform(strUpper.begin(), strUpper.end(), strUpper.begin(), toupper);
	return strUpper;
}

/**
 * @brief �ַ���ת��Сд
 * @param str [in] - Ҫת�����ַ���
 * @return ��ת�����ַ���
 */	
string ToLower(string str)
{
	string strLower = str;
	std::transform(strLower.begin(), strLower.end(), strLower.begin(), tolower);
	return strLower;
}

/**
 * @brief �����ִ�Сд�Ƚ�
 * @param str1 [in] - Ҫ�Աȵ��ַ���
 * @param str2 [in] - Ҫ�Աȵ��ַ���
 * @return 0 ���ȣ�1���
 */
int CompareNoCase(string str1, string str2)
{
	// ת�ɴ�д���Ƚ�
	return !ToUpper(str1).compare(ToUpper(str2));
}

/**
 * @brief �����ļ�����ƫ��λ�����뻺����
 * @param strFilePath [in] - �����ļ�·��
 * @param nFileSize [in] - �����ļ���С
 * @param nStart [in] - ��ʼƫ��λ��
 * @param nEnd [in] - ����ƫ��λ��
 * @return �ļ��Ļ���������
 */
char* GetFileContent(string strFilePath, long &nFileSize, long nStart, long nEnd)
{
	// �����Ϸ�У��
	if (strFilePath.compare("") == 0)
	{
		return NULL;
	}
	
	// ���ļ�����ͬfopen_s
	FILE* pFileInput = _fsopen(strFilePath.c_str(), "rb", _SH_DENYNO);
	if (pFileInput == NULL)
	{
		return NULL;
	}

	// ��ȡ�ļ���С
	fseek(pFileInput, 0, SEEK_END);
	
	nFileSize = ftell(pFileInput);
	rewind(pFileInput);

	if (nFileSize <= 0)
	{
		fclose(pFileInput); // �ر��ļ����

		return NULL;
	}

	// ���������Ч��
	if (nEnd >= (nFileSize - 1))
	{
		nEnd = nFileSize - 1;
	}

	long nReadNumber = 0;

	// ��ȡ����Ҫ���ڴ��С
	if (nStart == 0 && nEnd == 0)
	{
		nReadNumber = nFileSize;
	}
	else if (nEnd < nFileSize && nStart <= nEnd)
	{
		nReadNumber = nEnd - nStart + 1;

		// �ļ�ƫ�Ƶ���ʼλ��
		fseek(pFileInput, nStart, SEEK_SET);
	}
	else
	{
		fclose(pFileInput); //�ر��ļ����

		return NULL;
	}

	// ����ѿռ� - �ɵ������ͷ�
	char* pFileContent = new char[nReadNumber];

	if (pFileContent == NULL)
	{
		fclose(pFileInput);

		return NULL;
	}

	// �����ļ�����
	fread(pFileContent, sizeof(char), nReadNumber, pFileInput);

	// �ر��ļ����
	fclose(pFileInput);

	// �����ļ�������
	return pFileContent;
}

/**
 * @brief ����������д���ļ�
 * @param strFilePath [in] - �����ļ�·��
 * @param nFileSize [in] - ��������С
 * @param pFileContent [in] - ����������
 * @return �ɹ�ʧ��
 */
bool SetFileContent(string strFilePath, const char *pFileContent, long &nFileSize)
{
	// �����Ϸ�У��
	if (strFilePath.compare("") == 0 
		|| pFileContent == NULL
		|| nFileSize <= 0)
	{
		return false;
	}

	// ���ļ�����ͬfopen_s
	FILE* pFileOutput = _fsopen(strFilePath.c_str(), "wb", _SH_DENYWR);

	if (pFileOutput == NULL)
	{
		return false;
	}

	// ����������д���ļ�
	nFileSize = fwrite(pFileContent, sizeof(char), nFileSize, pFileOutput);

	// �ͷ��ļ����
	fclose(pFileOutput);

	return true;
}

/**
 * @brief ����������׷�ӵ��ļ�
 * @param strFilePath [in] - �����ļ�·��
 * @param nFileSize [in] - ��������С
 * @param pFileContent [in] - ����������
 * @return �ɹ�ʧ��
 */
bool AppendFileContent(string strFilePath, const char *pFileContent, long &nFileSize)
{
	// �����Ϸ�У��
	if (strFilePath.compare("") == 0 
		|| pFileContent == NULL
		|| nFileSize <= 0)
	{
		return false;
	}

	// ���ļ�����ͬfopen_s
	FILE* pFileOutput = _fsopen(strFilePath.c_str(), "ab", _SH_DENYWR);

	if (pFileOutput == NULL)
	{
		return false;
	}

	// ����׷��д���ļ�
	nFileSize = fwrite(pFileContent, sizeof(char), nFileSize, pFileOutput);

	// �ͷž��
	fclose(pFileOutput);

	return true;
}

/**
 * @brief ��ȡ�����ļ���С
 * @param strFilePath [in] - �����ļ�·��
 * @return �ļ���С
 */
long GetFileSize(string strFilePath)
{
	long nFileSize = 0;

	//��ȡ�ļ���С
	nFileSize = (long) GetFileSize64(strFilePath);
	if (nFileSize > 0)
	{
		return nFileSize;
	}

	// ������Ϸ�ʽʧ�ܣ����Ծɷ�ʽ��ȡ
	FILE* pFile = _fsopen(strFilePath.c_str(), "rb", _SH_DENYNO);
		
	if (pFile == NULL)
	{
		return -1; // �ļ�������
	}
	
	// ��ȡ�ļ���С
	fseek(pFile, 0, SEEK_END);

	nFileSize = ftell(pFile);
	rewind(pFile);

	// �ر��ļ����
	fclose(pFile);

	return nFileSize;
	
}

/**
 * @brief ��ȡ�����ļ���С
 * @param strFilePath [in] - �����ļ�·��
 * @return �ļ���С
 */
__int64 GetFileSize64(string strFilePath)
{ 
	struct __stat64 stFileStat;
	
	//��ȡ�ļ�����Ϣ
	if (_stat64(strFilePath.c_str(), &stFileStat) != 0)
	{
		return -1;
	}

	return stFileStat.st_size;
}

/**
 * @brief �Ƿ����ļ�
 * @param strFileName [in] - �����ļ�·��
 * @return �ǻ���
 */
bool IsFile(string strFilePath)
{
	std::ifstream ifsFile(strFilePath.c_str());

	//Ϊ�գ���ʾ���ļ�
	return (ifsFile != NULL);
}

/**
 * @brief ȡ������������
 * @param dNumber2Round [in] - С��ֵ
 * @return ����ֵ
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
 * @brief �Ƿ�ż��
 * @param nNumber [in] -  ����
 * @return �� ture���� false
 */
bool IsPowerOf2(unsigned long nNumber)
{
	return ((nNumber & (nNumber - 1)) == 0);
}
/**
 * @brief ����ת�ַ���
 * @param nNumber [in] - ����ֵ
 * @return �ַ���
 */
string Long2String(long nNumber)
{
	std::ostringstream strStream;
	strStream << nNumber;

	return strStream.str();
}

/**
 * @brief С��ת�ַ���
 * @param dNumber [in] - С��ֵ
 * @param nPrecision [in] - ����
 * @return �ַ���
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
 * @brief ��ȡϵͳʱ��
 * @param strDateFormat [in] - ʱ���ʽ
 * @return ϵͳʱ�䣬�ַ���
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
 * @brief ��ȡϵͳʱ��
 * @param strDateFormat [in] - ʱ���ʽ
 * @return ϵͳʱ�䣬�ַ���
 */
string GetSystemTime(string strDateFormat)
{
	time_t ttCurrentTime = 0;
	time(&ttCurrentTime);

	return GetSystemTime(ttCurrentTime, strDateFormat);
}

/**
 * @brief ��ת����ʱ����
 * @param strTime [in] -  ����
 * @return ʱ����
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
 * @brief ʱ����ת������
 * @param strTime [in] - ʱ��
 * @return ����
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

//�ڲ��ӿ�
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


//�ڲ��ӿ�
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

//�ڲ��ӿ�
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

//�ڲ��ӿ�
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
 * @brief �����ļ��У��������ļ���
 * @param strDirPath [in] - Ŀ¼·��
 * @return ��
 */

void MakeDirectory(string strDirPath)
{
	// �����Ϸ�У��
	if (strDirPath.compare(_T("")) == 0)
	{
		return;
	}

	string strDirPathCopy = RemoveDirectoryEnding(strDirPath);

	// ��ȡб�˵ĸ���
	long nCount = GetTokenCount(strDirPathCopy, DIRECTORY_SEPARATOR);

	// ��ȡĿ¼��
	string strDir = GetToken(strDirPathCopy, DIRECTORY_SEPARATOR, 0);

	long nIndex = 0;

	// ѭ�����δ�����Ŀ¼
	for (nIndex = 1; nIndex < nCount; nIndex++)
	{
		strDir += DIRECTORY_SEPARATOR;
		strDir += GetToken(strDirPathCopy, DIRECTORY_SEPARATOR, nIndex);

		CreateDirectory(strDir.c_str(), NULL);
		SetFileAttributes(strDir.c_str(), FILE_ATTRIBUTE_NORMAL);
	}

}

/**
 * @brief ɾ���ļ��У��������ļ���
 * @param strDirPath [in] - Ŀ¼·��
 * @return �ļ�����·��
 */
void DeleteDirectory(string strDirPath)
{
	// �����Ϸ���֤
	if (strDirPath.compare(_T("")) == 0)
	{
		return;
	}

	// ȥ��ĩβ��б��'\'
	string strCurrDir = RemoveDirectoryEnding(strDirPath);

	// ƴװ����·���ַ���
	string strDesPath;
	strDesPath += "\\\\?\\";
	strDesPath += strCurrDir;
	strDesPath = AddDirectoryEnding(strDesPath);
	strDesPath += "*.*";

	// Ҫɾ����·��
	string strDelDir;
	strDelDir += "\\\\?\\";
	strDelDir += strCurrDir;

	WIN32_FIND_DATA stDesktop = {0};

	HANDLE hDesktop = ::FindFirstFile(strDesPath.c_str(), &stDesktop);	

	// ����ʧ�ܣ���ʾ�ļ���Ϊ��
	if (hDesktop == INVALID_HANDLE_VALUE)
	{
		// ɾ���ļ���
		RemoveDirectory(strDelDir.c_str());

		return;
	}

	do 
	{
		// ����·��
		string strPath = _T("");
		strPath += strCurrDir;
		strPath = AddDirectoryEnding(strPath);
		strPath += stDesktop.cFileName;

		// �Ƿ��ҵ��ļ���
		if (stDesktop.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// ��ȡĿ¼����
			string strCurrDirName = GetDirectoryName(strPath);

			if (strCurrDirName == "." || strCurrDirName == "..")
			{
				continue;
			}
			else
			{
				// �ݹ�ɾ��
				DeleteDirectory(strPath);
			}
		}
		else 
		{
			//�ҵ��ļ���ɾ���ļ�
			_tunlink(strPath.c_str());
		}
	}
	while (::FindNextFile(hDesktop, &stDesktop) == TRUE);

	// �رվ��
	::FindClose(hDesktop);

	// ɾ���ļ���
	RemoveDirectory(strDelDir.c_str());
}



