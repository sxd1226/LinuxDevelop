#pragma once
#ifdef _WIN64
#include <crtdbg.h>
#include <tchar.h>
#include <WinSock2.h>
#else

#include <wchar.h>
#include <iconv.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************
��������WCharToMultiChar
���ܣ����ֽ�ת��Ϊ���ֽ�
������
	��
����ֵ��
************************************************************************/




/************************************************************************
��������MultiCharToWChar
���ܣ����ֽ�ת��Ϊ���ֽ�
������
	��
����ֵ��
************************************************************************/

