#include "stdafx.h"

int main()
{
    printf("%s 向你问好!\n", "LinuxDevelop");
    int ret = 0;

    //Linux下宽字节转换为多字节
    wchar_t wstr[] = L"Hello, World!";
    ret = wcstombs(NULL, wstr, 0) + 1;//第一参数为NULL时函数将返回转换所需的正确大小
    if (-1 == ret)
    {
        printf("wcstombs转换失败!\n");
        return 0;
    }
    printf("转换所需%d Char\n", ret);
    // 计算输入字符串的长度
    size_t wlen = wcslen(wstr) * sizeof(wchar_t);
    // 定义输出字符串的缓冲区和缓冲区大小
    char* output_buffer = (char*)malloc(wlen * 4);
    size_t output_buffer_size = wlen * 4;

    ret = wcstombs(output_buffer, wstr, output_buffer_size);
    if (-1 == ret)
    {
        printf("wcstombs转换失败!\n");
        return 0;
    }
    printf("要转换%d Char\n", ret);
    //{   
    //    // 创建 iconv 对象
    //    iconv_t cd = iconv_open("GBK", "UTF-8");
    //    // 进行转换
    //    iconv(cd, (char**)&wstr, &wlen, &output_buffer, &output_buffer_size);

    //    // 关闭 iconv 对象
    //    iconv_close(cd);
    //}

    // 输出转换后的字符串
    printf("%s\n", output_buffer);

    //释放字符串缓冲区
    free(output_buffer);

    //测试获取系统时间
    FILE* m_pFile;
    tm* pTime;
    struct timeval    tv;
    struct timezone   tz;

    char    sCurrentFile[1024];
    char	sRemoveFile[1024];
    char    m_sCurrentFile[1024];
    char    m_sLogBuffer[1024];
    char	sSuffix[1024], * pc;
    char    strLogDir[1024] = "/home/run/LinuxTimeTest/log";
    char    m_sDefaultFile[1024] = "/home/run/LinuxTimeTest/log/TimeTest.log";

    printf("strLogDir :%s\n", strLogDir);
    if (access(strLogDir, 0) == -1)//access函数是查看文件是不是存在
    {
        if (mkdir(strLogDir, 0777))//如果不存在就用mkdir函数来创建
        {
            printf("creat file bag failed!!!");
        }
    }

    while (1)
    {
        gettimeofday(&tv, &tz);
        pTime = localtime(&tv.tv_sec);

        if (pTime)
        {
            sprintf(sCurrentFile, "%s", m_sDefaultFile);
            pc = strstr(sCurrentFile, ".log");
            if (pc)
            {
                sprintf(sSuffix, "%s", pc);
                sprintf(pc, "_%04d%02d%02d%02d%s", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour, sSuffix);
            }
            else
            {
                sprintf(sCurrentFile + strlen(sCurrentFile), "_%04d%02d%02d%02d", pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour);
            }
            printf("Date: %04d%02d%02d %02d:%02d:%02d.%03lld\nFileName: %s\n",
                pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour,
                pTime->tm_min, pTime->tm_sec, tv.tv_usec / 1000, sCurrentFile);
        }

        if (strcmp(m_sCurrentFile, sCurrentFile) != 0)
        {
            sprintf(sRemoveFile, "%s", m_sDefaultFile);
            pc = strstr(sRemoveFile, ".log");
            if (pc)
            {
                sprintf(sSuffix, "%s", pc);
                sprintf(pc, "_%04d%02d%02d%02d%s", pTime->tm_year + 1900 - 1, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour, sSuffix);
            }
            else
            {
                sprintf(sRemoveFile + strlen(sRemoveFile), "_%04d%02d%02d%02d", pTime->tm_year + 1900 - 1, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour);
            }

            remove(sRemoveFile);

            if (m_pFile)
            {
                fclose(m_pFile);
                m_pFile = NULL;
            }

            sprintf(m_sCurrentFile, "%s", sCurrentFile);

            m_pFile = fopen(m_sCurrentFile, "a+");
        }

        if (m_pFile)
        {
            memset(m_sLogBuffer, 0, sizeof(m_sLogBuffer));
            sprintf(m_sLogBuffer, "%04d-%02d-%02d %02d:%02d:%02d.%03lld\t%s\r\n", 
                pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, tv.tv_usec / 1000, m_sCurrentFile);
            fwrite(m_sLogBuffer, 1, strlen(m_sLogBuffer), m_pFile);
            fflush(m_pFile);
        }

        sleep(5);
    }

    return 0;
}