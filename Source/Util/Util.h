/************************************************************
Copyright (C), START LIMITED 2019

File name: Util.h

Author: zhangjh		Version: 1.0	Date: 2019-08-13 

Description:  ������ƽ���õ��Ĳ���ͨ�ýӿڣ����ڿ�׷�ӽӿ�

History:

1. Date:
   Author:
   Modification:

*************************************************************/

#include <atlbase.h>
#include <sys\stat.h> 


//Ŀ¼·���ָ���
#define DIRECTORY_SEPARATOR		"\\"
#define DIRECTORY_SEPARATOR_C		'\\'


/* ע������ */

/**
 * @brief ��ȡע����Ӽ����ַ���ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @return �ַ����ļ�ֵ
 */
string GetRegistryInfo(HKEY hKey, string strRegPath, string strName);

/**
 * @brief ��ȡע����Ӽ�������ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @return ���εļ�ֵ
 */
DWORD GetRegistryValue(HKEY hKey, string strRegPath, string strName);

/**
 * @brief ����ע����Ӽ����ַ���ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @param strName [in] - �Ӽ����ַ���ֵ
 * @return �ɹ�ture��ʧ��false
 */
bool SetRegistryInfo(HKEY hkey, string strRegPath, string strName, string strValue);

/**
 * @brief ����ע����Ӽ�������ֵ
 * @param hKey [in] - ע����
 * @param strRegPath [in] - ע���·��
 * @param strName [in] - �Ӽ�������
 * @param strName [in] - �Ӽ�������ֵ
 * @return �ɹ�ture��ʧ��false
 */
bool SetRegistryValue(HKEY hkey, string strRegPath, string strName, DWORD dwValue);



/* ִ�в��� */

/**
 * @brief  ִ��һ����ִ�е��ļ�
 * @param strFileName [in] - �����ļ�������
 * @param strParam [in] - ����Ĳ���
 * @param bShow [in] - �Ƿ���ʾ����
 * @param bWait [in] - �Ƿ�ȴ������˳�
 * @return �ɹ�ture��ʧ��false
 */
bool Execute(string strFilePath, string strParam
			 , bool bShow = true
			 , bool bWait = false
			 );

/**
 * @brief  ִ��������
 * @param strCmdLine [in] - ������
 * @param bShow [in] - �Ƿ���ʾ����
 * @param bWait [in] - �Ƿ�ȴ�ִ�����
 * @return �ɹ�ture��ʧ��false
 */
bool Execute(string strCmdLine, bool bShow = true, bool bWait = false);



/* ��ȡ����·�� */

/**
 * @brief ��ȡ��ǰ����·��
 * @return ����·��
 */
string GetWorkingDirectory();

/**
 * @brief ��ȡ��ǰ����ľ���·��
 * @return ����·��
 */
string GetProgramDirectory();

	

/* �ַ������� */

/**
 * @brief �����滻�ַ���
 * @param strSource [in] - Դ�ַ���
 * @param strFind [in] - Ҫ���ҵ��ַ���
 * @param strReplace [in] - �滻���ַ���
 * @return �滻�Ĵ���
 */		
long FindReplace(string &strSource, string strFind, string strReplace);

/**
 * @brief �ַ���ȥ���ո�
 * @param strSource [in] - Դ�ַ���
 * @param strReplace [in] - ���滻�Ĵ�
 * @return ��
 */
void RemoveWhiteSpaces(string &strSource, string strReplace = "");

/**
 * @brief ȥ�����ҿո񡢻���
 * @param strSource [in] - Դ�ַ���
 * @param strTrim [in] - Ҫȥ���Ĵ�
 * @param bLeft [in] - �Ƿ�ȥ����
 * @param bRight [in] - �Ƿ�ȥ����
 * @return ��
 */
void Trim(string &strSource, string strTrim = " \t\r\n"
		  , bool bLeft = true
		  , bool bRight = true
		  );

/**
 * @brief ��ȡ�ָ���ĸ���
 * @param strSource [in] - Դ�ַ���
 * @param strSource [in] - �ָ���
 * @return �ָ���ĸ���
 */
long GetTokenCount(string strSource, string strDelimiter);

/**
 * @brief ���ݷָ���˳���ȡ�ַ���
 * @param strSource [in] - Դ�ַ���
 * @param strSource [in] - �ָ���
 * @param nTokenIndex [in] - �ָ������,��0��ʼ
 * @return ��ȡ���ַ���
 */
string GetToken(string strSource, string strDelimiter, long nTokenIndex);
	
/**
 * @brief �ַ���ת�ɴ�д
 * @param str [in] - Ҫת�����ַ���
 * @return ��ת�����ַ���
 */	
string ToUpper(string str);

/**
 * @brief �ַ���ת��Сд
 * @param str [in] - Ҫת�����ַ���
 * @return ��ת�����ַ���
 */	
string ToLower(string str);

/**
 * @brief �����ִ�Сд�Ƚ�
 * @param str1 [in] - Ҫ�Աȵ��ַ���
 * @param str2 [in] - Ҫ�Աȵ��ַ���
 * @return 0 ���ȣ�1���
 */
int CompareNoCase(string str1, string str2);



/* ���ֲ��� */

/**
 * @brief ����ת�ַ���
 * @param nNumber [in] - ����ֵ
 * @return �ַ���
 */
string Long2String(long nNumber);

/**
 * @brief С��ת�ַ���
 * @param dNumber [in] - С��ֵ
 * @param nPrecision [in] - ����
 * @return �ַ���
 */
string Double2String(double dNumber, long nPrecision = 0);

/**
 * @brief ȡ������������
 * @param dNumber2Round [in] - С��ֵ
 * @return ����ֵ
 */
long Round(double dNumber2Round);

/**
 * @brief �Ƿ�ż��
 * @param nNumber [in] -  ����
 * @return �� ture���� false
 */
bool IsPowerOf2(unsigned long nNumber);



/* ʱ����� */

/**
 * @brief ��ȡϵͳʱ��
 * @param strDateFormat [in] - ʱ���ʽ
 * @return ϵͳʱ�䣬�ַ���
 */
string GetSystemTime(string strDateFormat = "%A, %d/%m/%Y, %H:%M:%S - %Z");

/**
 * @brief ��ת����ʱ����
 * @param strTime [in] -  ����
 * @return ʱ����
 */
string GetTime(long lSeconds);

/**
 * @brief ʱ����ת������
 * @param strTime [in] - ʱ��
 * @return ����
 */
long GetTime(string strTime = "00:00:00");



/* �ļ�IO�ӿ� */

/**
 * @brief �����ļ�����ƫ��λ�����뻺����
 * @param strFilePath [in] - �����ļ�·��
 * @param nFileSize [in] - �����ļ���С
 * @param nStart [in] - ��ʼƫ��λ��
 * @param nEnd [in] - ����ƫ��λ��
 * @return �ļ��Ļ���������
 */
char* GetFileContent(string strFilePath, long &nFileSize, long nStart = 0, long nEnd = 0);

/**
 * @brief ����������д���ļ�
 * @param strFilePath [in] - �����ļ�·��
 * @param nFileSize [in] - ��������С
 * @param pFileContent [in] - ����������
 * @return �ɹ�ʧ��
 */
bool SetFileContent(string strFilePath, const char *pFileContent, long &nFileSize);

/**
 * @brief ����������׷�ӵ��ļ�
 * @param strFilePath [in] - �����ļ�·��
 * @param nFileSize [in] - ��������С
 * @param pFileContent [in] - ����������
 * @return �ɹ�ʧ��
 */
bool AppendFileContent(string strFilePath, const char *pFileContent, long &nFileSize);

/**
 * @brief ��ȡ�����ļ���С
 * @param strFilePath [in] - �����ļ�·��
 * @return �ļ���С
 */
long GetFileSize(string strFilePath);
__int64 GetFileSize64(string strFilePath);

/**
 * @brief �Ƿ����ļ�
 * @param strFileName [in] - �����ļ�·��
 * @return �ǻ���
 */
bool IsFile(string strFilePath);



/* �ļ��в��� */

/**
 * @brief �����ļ��У��������ļ���
 * @param strDirPath [in] - Ŀ¼·��
 * @return ��
 */
void MakeDirectory(string strDirPath);

/**
 * @brief ɾ���ļ��У��������ļ���
 * @param strDirPath [in] - Ŀ¼·��
 * @return �ļ�����·��
 */
void DeleteDirectory(string strDirPath);


	

