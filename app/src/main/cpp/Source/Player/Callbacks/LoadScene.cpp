#include <jni.h>

#include <Runtime/Log/Log.h>
#include <Application/RenderEngine/Scenes/SceneType.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kotlintest_callbacks_LoadCallbacks_LoadScene(JNIEnv *env, jclass clazz, jobject scene_id) {
    jclass enumClass = env->GetObjectClass(scene_id);
    jmethodID getIdMethod = env->GetMethodID(enumClass, "getId", "()I");
    jint nativeId = env->CallIntMethod(scene_id, getIdMethod);

    auto sceneType = static_cast<SceneType>(nativeId);

    std::string sceneName;
    switch(sceneType)
    {
        case SceneType::Sponza:
            sceneName = "Sponza";
            break;
        case SceneType::Helmet:
            sceneName = "Helmet";
            break;
        default:
        case SceneType::Unknown:
            sceneName = "Unknown";
            break;
    }

    Log::Info("LoadScene called directly from object! ID: {}", sceneName);
}