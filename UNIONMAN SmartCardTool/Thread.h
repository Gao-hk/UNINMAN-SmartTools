// Thread.h
#pragma once
#include <process.h>
#include <Windows.h>

#define WM_USER_MSG WM_USER + 1001
class CThread
{
public:
    // �̻߳ص�����������ȫ�ֺ���
    static void Run(void *ptr);
public:
    CThread(void);
    ~CThread(void);
};