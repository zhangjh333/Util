/************************************************************
Copyright (C), START LIMITED 2019

File name: Template.h

Author: zhangjh		Version: 1.0	Date: 2019-08-22 

Description:  编程规范模板

History:

1. Date:
   Author:
   Modification:

*************************************************************/

#if 0

编程规范遵循以下几点：

1、变量：

前缀+词+词，一般两个词即可。

前缀的规则如下：

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


2、常用类型

宏:
#define ERR_INSTALL_DRIVER	0

结构体:
typedef struct DriverConfig 
{
	...

}DRIVER_CONFIG;

枚举:
typedef enum DriveType
{
	...

}DRIVE_TYPE;

类:
class CInstallManager
{
	...
};


3、函数：

函数名首字母大写。

参数的命名规则与变量相同。

参数的逗号紧跟空格。

参数的个数不能超过5个。

参数的数据保护要加const。

参数要做合法性检查

函数体实现不能过长，一般控制在一页可见。

函数体大括号不能嵌套太深，一般不能超过四层。

函数体要处理失败的情况，保证稳定的执行。

函数错误返回值，要用宏定义，清晰可读


4、注释

文件需要有文件头注释，注明作者、日期、描述等。

注释的位置只能是代码行的上方和右方。

函数头的注释格式，如下代码所示。

函数体需要分段注释。


5、空格

if、for、while、switch等关键字紧跟空格。

二元运算符使用空格隔开

注释符号紧跟空格。

逗号紧跟空格。


6、头文件

只存放对外接口的声明，对内接口无需放在头文件里。

CPP文件包含头文件时，顺序遵循不稳定的在前。

要做到自包含。

#endif


#ifndef TEMPLETE_H
#define TEMPLETE_H

// 返回值定义
#define RET_OK				0
#define RET_ERR_PARAM		1
#define RET_ERR_INSTALL		2

/**
 * @brief 函数的规范模板
 * @param strCmdLine [in] - 参数
 * @param bShow [in] - 参数
 * @param pData [in] - 参数
 * @return 返回值
 */

bool StandardTemplete(string strCmdLine, bool bShow, const char *pData);

#endif

