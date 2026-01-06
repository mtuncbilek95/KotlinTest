#include "NativeApplication.h"

#include <Runtime/Graphics/Instance/VInstance.h>

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <game-activity/GameActivity.h>

#include <Runtime/Log/Log.h>

#include <thread>

NativeApplication::NativeApplication(android_app *pApp) : mMainApp(pApp) {
}

bool NativeApplication::OnInvalidate() {
    return false;
}

SystemReport NativeApplication::OnInitialize() {
    if (!mMainApp) {
        Log::Fatal("MainApplication has not set for engine!");
        return SystemReport("Exiting due to not having android_app*");
    }

    mMainApp->onAppCmd = HandleCommand;
    android_app_set_motion_event_filter(mMainApp, MotionFilterEvent);

    Log::Verbose("Successfully initialized NativeApplication!");

    VInstance* pInstance = new VInstance();
    return SystemReport();
}

void NativeApplication::OnFinalize() {
    Log::Verbose("Successfully finalized NativeApplication!");
}

void NativeApplication::HandleCommand(android_app *pApp, int32_t cmd) {
    auto* engine = static_cast<NativeApplication*>(pApp->userData);

    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            if (pApp->window != nullptr) {
                // engine->InitializeGraphics();

                Log::Info("Window Initialized. Surface is ready.");
            }
            break;

        case APP_CMD_TERM_WINDOW:
            // engine->ShutdownGraphics();
            Log::Info("Window Terminated.");
            break;

        case APP_CMD_DESTROY:
            Log::Info("App Destroyed.");
            break;

        default:
            break;
    }
}

bool NativeApplication::MotionFilterEvent(const GameActivityMotionEvent *pEvent) {
    auto sourceClass = pEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

void NativeApplication::OnRun() {
    do {
        bool done = false;
        while (!done) {
            int timeout = 0;
            int events;
            android_poll_source *pSource;
            int result = ALooper_pollOnce(timeout, nullptr, &events,
                                          reinterpret_cast<void **>(&pSource));
            switch (result) {
                case ALOOPER_POLL_TIMEOUT:
                    [[clang::fallthrough]];
                case ALOOPER_POLL_WAKE:
                    done = true;
                    break;
                case ALOOPER_EVENT_ERROR:
                    break;
                case ALOOPER_POLL_CALLBACK:
                    break;
                default:
                    if (pSource) {
                        pSource->process(mMainApp, pSource);
                    }
            }
        }

        // Check if any user data is associated. This is assigned in handle_cmd
        if (mMainApp->userData) {
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    } while (!mMainApp->destroyRequested);
}
