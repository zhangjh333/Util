#include "stdafx.h"
#include "Util.h"

int main()
{
	string strValue;
	DWORD dwValue = 0;
	long n = 0;
	
	string s("+++");
	string s1("aS");

	n = GetTime(string("00:20:34"));

	n = GetFileSize(".\\test.txt");

	n = s.length();

	AppendFileContent(".\\test.txt",s.c_str(),n);

	DeleteDirectory("D:\\a");

	return 0;
}