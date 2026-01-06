#include <Application/NativeEngine/NativeApplication.h>

extern "C" {

void android_main(struct android_app *pApp) {
    NativeApplication nativeApp(pApp);

    if (nativeApp.OnInitialize().IsExitRequested())
        return;

    nativeApp.OnRun();
    nativeApp.OnFinalize();
}

}
