/************************************************************
Copyright (C), START LIMITED 2019

File name: Template.h

Author: zhangjh		Version: 1.0	Date: 2019-08-22 

Description:  ��̹淶ģ��

History:

1. Date:
   Author:
   Modification:

*************************************************************/

#if 0

��̹淶��ѭ���¼��㣺

1��������

ǰ׺+��+�ʣ�һ�������ʼ��ɡ�

ǰ׺�Ĺ������£�

int\short\long\unsignd  -- n
float					-- f
double					-- d
bool					-- b
string\cstring			-- str
char []					-- sz
char *					-- psz
point *					-- p
enum					-- em
struct					-- st
class					-- ob
global					-- g_
static					-- s_
member					-- m_


2����������

��:
#define ERR_INSTALL_DRIVER	0

�ṹ��:
typedef struct DriverConfig 
{
	...

}DRIVER_CONFIG;

ö��:
typedef enum DriveType
{
	...

}DRIVE_TYPE;

��:
class CInstallManager
{
	...
};


3��������

����������ĸ��д��

���������������������ͬ��

�����Ķ��Ž����ո�

�����ĸ������ܳ���5����

���������ݱ���Ҫ��const��

����Ҫ���Ϸ��Լ��

������ʵ�ֲ��ܹ�����һ�������һҳ�ɼ���

����������Ų���Ƕ��̫�һ�㲻�ܳ����Ĳ㡣

������Ҫ����ʧ�ܵ��������֤�ȶ���ִ�С�

�������󷵻�ֵ��Ҫ�ú궨�壬�����ɶ�


4��ע��

�ļ���Ҫ���ļ�ͷע�ͣ�ע�����ߡ����ڡ������ȡ�

ע�͵�λ��ֻ���Ǵ����е��Ϸ����ҷ���

����ͷ��ע�͸�ʽ�����´�����ʾ��

��������Ҫ�ֶ�ע�͡�


5���ո�

if��for��while��switch�ȹؼ��ֽ����ո�

��Ԫ�����ʹ�ÿո����

ע�ͷ��Ž����ո�

���Ž����ո�


6��ͷ�ļ�

ֻ��Ŷ���ӿڵ����������ڽӿ��������ͷ�ļ��

CPP�ļ�����ͷ�ļ�ʱ��˳����ѭ���ȶ�����ǰ��

Ҫ�����԰�����

#endif


#ifndef TEMPLETE_H
#define TEMPLETE_H

// ����ֵ����
#define RET_OK				0
#define RET_ERR_PARAM		1
#define RET_ERR_INSTALL		2

/**
 * @brief �����Ĺ淶ģ��
 * @param strCmdLine [in] - ����
 * @param bShow [in] - ����
 * @param pData [in] - ����
 * @return ����ֵ
 */

bool StandardTemplete(string strCmdLine, bool bShow, const char *pData);

#endif

