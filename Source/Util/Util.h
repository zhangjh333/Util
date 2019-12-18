/************************************************************
Copyright (C), START LIMITED 2019

File name: Util.h

Author: zhangjh		Version: 1.0	Date: 2019-08-13 

Description:  整理了平常用到的部分通用接口，后期可追加接口

History:

1. Date:
   Author:
   Modification:

*************************************************************/

#include <atlbase.h>
#include <sys\stat.h> 


//目录路径分隔符
#define DIRECTORY_SEPARATOR		"\\"
#define DIRECTORY_SEPARATOR_C		'\\'


/* 注册表操作 */

/**
 * @brief 获取注册表子键的字符串值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @return 字符串的键值
 */
string GetRegistryInfo(HKEY hKey, string strRegPath, string strName);

/**
 * @brief 获取注册表子键的整形值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @return 整形的键值
 */
DWORD GetRegistryValue(HKEY hKey, string strRegPath, string strName);

/**
 * @brief 设置注册表子键的字符串值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @param strName [in] - 子键的字符串值
 * @return 成功ture，失败false
 */
bool SetRegistryInfo(HKEY hkey, string strRegPath, string strName, string strValue);

/**
 * @brief 设置注册表子键的整形值
 * @param hKey [in] - 注册表键
 * @param strRegPath [in] - 注册表路径
 * @param strName [in] - 子键的名称
 * @param strName [in] - 子键的整形值
 * @return 成功ture，失败false
 */
bool SetRegistryValue(HKEY hkey, string strRegPath, string strName, DWORD dwValue);



/* 执行操作 */

/**
 * @brief  执行一个可执行的文件
 * @param strFileName [in] - 本地文件的名称
 * @param strParam [in] - 传入的参数
 * @param bShow [in] - 是否显示界面
 * @param bWait [in] - 是否等待程序退出
 * @return 成功ture，失败false
 */
bool Execute(string strFilePath, string strParam
			 , bool bShow = true
			 , bool bWait = false
			 );

/**
 * @brief  执行命令行
 * @param strCmdLine [in] - 命令行
 * @param bShow [in] - 是否显示界面
 * @param bWait [in] - 是否等待执行完毕
 * @return 成功ture，失败false
 */
bool Execute(string strCmdLine, bool bShow = true, bool bWait = false);



/* 获取程序路径 */

/**
 * @brief 获取当前工作路径
 * @return 工作路径
 */
string GetWorkingDirectory();

/**
 * @brief 获取当前程序的绝对路径
 * @return 绝对路径
 */
string GetProgramDirectory();

	

/* 字符串操作 */

/**
 * @brief 查找替换字符串
 * @param strSource [in] - 源字符串
 * @param strFind [in] - 要查找的字符串
 * @param strReplace [in] - 替换的字符串
 * @return 替换的次数
 */		
long FindReplace(string &strSource, string strFind, string strReplace);

/**
 * @brief 字符串去除空格
 * @param strSource [in] - 源字符串
 * @param strReplace [in] - 被替换的串
 * @return 无
 */
void RemoveWhiteSpaces(string &strSource, string strReplace = "");

/**
 * @brief 去除左右空格、换行
 * @param strSource [in] - 源字符串
 * @param strTrim [in] - 要去除的串
 * @param bLeft [in] - 是否去除左
 * @param bRight [in] - 是否去除右
 * @return 无
 */
void Trim(string &strSource, string strTrim = " \t\r\n"
		  , bool bLeft = true
		  , bool bRight = true
		  );

/**
 * @brief 获取分割符的个数
 * @param strSource [in] - 源字符串
 * @param strSource [in] - 分隔符
 * @return 分割符的个数
 */
long GetTokenCount(string strSource, string strDelimiter);

/**
 * @brief 根据分隔符顺序截取字符串
 * @param strSource [in] - 源字符串
 * @param strSource [in] - 分隔符
 * @param nTokenIndex [in] - 分隔符序号,从0开始
 * @return 截取的字符串
 */
string GetToken(string strSource, string strDelimiter, long nTokenIndex);
	
/**
 * @brief 字符串转成大写
 * @param str [in] - 要转化的字符串
 * @return 已转化的字符串
 */	
string ToUpper(string str);

/**
 * @brief 字符串转成小写
 * @param str [in] - 要转化的字符串
 * @return 已转化的字符串
 */	
string ToLower(string str);

/**
 * @brief 不区分大小写比较
 * @param str1 [in] - 要对比的字符串
 * @param str2 [in] - 要对比的字符串
 * @return 0 不等，1相等
 */
int CompareNoCase(string str1, string str2);



/* 数字操作 */

/**
 * @brief 整形转字符串
 * @param nNumber [in] - 整形值
 * @return 字符串
 */
string Long2String(long nNumber);

/**
 * @brief 小数转字符串
 * @param dNumber [in] - 小数值
 * @param nPrecision [in] - 精度
 * @return 字符串
 */
string Double2String(double dNumber, long nPrecision = 0);

/**
 * @brief 取整，四舍五入
 * @param dNumber2Round [in] - 小数值
 * @return 整形值
 */
long Round(double dNumber2Round);

/**
 * @brief 是否偶数
 * @param nNumber [in] -  数字
 * @return 是 ture，否 false
 */
bool IsPowerOf2(unsigned long nNumber);



/* 时间操作 */

/**
 * @brief 获取系统时间
 * @param strDateFormat [in] - 时间格式
 * @return 系统时间，字符串
 */
string GetSystemTime(string strDateFormat = "%A, %d/%m/%Y, %H:%M:%S - %Z");

/**
 * @brief 秒转换成时分秒
 * @param strTime [in] -  秒数
 * @return 时分秒
 */
string GetTime(long lSeconds);

/**
 * @brief 时分秒转化成秒
 * @param strTime [in] - 时间
 * @return 秒数
 */
long GetTime(string strTime = "00:00:00");



/* 文件IO接口 */

/**
 * @brief 本地文件根据偏移位置载入缓冲区
 * @param strFilePath [in] - 本地文件路径
 * @param nFileSize [in] - 本地文件大小
 * @param nStart [in] - 开始偏移位置
 * @param nEnd [in] - 结束偏移位置
 * @return 文件的缓冲区数据
 */
char* GetFileContent(string strFilePath, long &nFileSize, long nStart = 0, long nEnd = 0);

/**
 * @brief 缓冲区数据写入文件
 * @param strFilePath [in] - 本地文件路径
 * @param nFileSize [in] - 缓冲区大小
 * @param pFileContent [in] - 缓冲区数据
 * @return 成功失败
 */
bool SetFileContent(string strFilePath, const char *pFileContent, long &nFileSize);

/**
 * @brief 缓冲区数据追加到文件
 * @param strFilePath [in] - 本地文件路径
 * @param nFileSize [in] - 缓冲区大小
 * @param pFileContent [in] - 缓冲区数据
 * @return 成功失败
 */
bool AppendFileContent(string strFilePath, const char *pFileContent, long &nFileSize);

/**
 * @brief 获取本地文件大小
 * @param strFilePath [in] - 本地文件路径
 * @return 文件大小
 */
long GetFileSize(string strFilePath);
__int64 GetFileSize64(string strFilePath);

/**
 * @brief 是否是文件
 * @param strFileName [in] - 本地文件路径
 * @return 是或不是
 */
bool IsFile(string strFilePath);



/* 文件夹操作 */

/**
 * @brief 创建文件夹，包含子文件夹
 * @param strDirPath [in] - 目录路径
 * @return 无
 */
void MakeDirectory(string strDirPath);

/**
 * @brief 删除文件夹，包含子文件夹
 * @param strDirPath [in] - 目录路径
 * @return 文件绝对路径
 */
void DeleteDirectory(string strDirPath);


	

