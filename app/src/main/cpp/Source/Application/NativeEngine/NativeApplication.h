#pragma once

#include <cstdio>
#include <Runtime/Reporter/SystemReport.h>

struct android_app;
struct GameActivityMotionEvent;

class NativeApplication {
public:
    explicit NativeApplication(android_app* pApp);
    ~NativeApplication() = default;

    bool OnInvalidate();
    SystemReport OnInitialize();
    void OnRun();
    void OnFinalize();

private:
    static void HandleCommand(android_app *pApp, int32_t cmd);
    static bool MotionFilterEvent(const GameActivityMotionEvent* pEvent);

private:
    android_app* mMainApp;
};