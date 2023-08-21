#define LOG_TAG "native_start_java"

#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <android-base/macros.h>
#include <binder/IPCThreadState.h>
#include <utils/Log.h>
#include <cutils/memory.h>
#include <cutils/properties.h>
#include <cutils/trace.h>
#include <android_runtime/AndroidRuntime.h>
#include <private/android_filesystem_config.h>  // for AID_SYSTEM

namespace android {

class AppRuntime : public AndroidRuntime
{
public:
    AppRuntime(char* argBlockStart, const size_t argBlockLength)
        : AndroidRuntime(argBlockStart, argBlockLength)
        , mClass(NULL)
    {
    }

    void setClassNameAndArgs(const String8& className, int argc, char * const *argv) {
        mClassName = className;
        for (int i = 0; i < argc; ++i) {
             mArgs.add(String8(argv[i]));
        }
    }

    virtual void onVmCreated(JNIEnv* env)
    {
        if (mClassName.isEmpty()) {
            return; // Zygote. Nothing to do here.
        }

        char* slashClassName = toSlashClassName(mClassName.string());
        mClass = env->FindClass(slashClassName);
        if (mClass == NULL) {
            ALOGE("ERROR: could not find class '%s'\n", mClassName.string());
        }
        free(slashClassName);

        mClass = reinterpret_cast<jclass>(env->NewGlobalRef(mClass));
    }


    virtual void onStarted()
    {
        sp<ProcessState> proc = ProcessState::self();
        ALOGV("App process: starting thread pool.\n");
        proc->startThreadPool();

        AndroidRuntime* ar = AndroidRuntime::getRuntime();
        ar->callMain(mClassName, mClass, mArgs);

        IPCThreadState::self()->stopProcess();
    }

    String8 mClassName;
    Vector<String8> mArgs;
    jclass mClass;
};
}

using namespace android;
int main(int argc, char* const argv[])
{
    Vector<String8> args;
    AppRuntime runtime(0, 0);
    runtime.setClassNameAndArgs(String8("com.example.TestJava"), 0, nullptr);
    args.add(String8("application"));

    runtime.start("com.android.internal.os.RuntimeInit", args, false);
}
