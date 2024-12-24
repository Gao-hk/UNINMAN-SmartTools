// Thread.h
#pragma once
#include <process.h>
#include <Windows.h>

#define WM_USER_MSG WM_USER + 1001
class CThread
{
public:
    // 线程回调函数必须是全局函数
    static void Run(void *ptr);
public:
    CThread(void);
    ~CThread(void);
};