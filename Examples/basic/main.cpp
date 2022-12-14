/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

 //BEGIN_INCLUDE(all)
#include <initializer_list>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cassert>


#if __ANDROID__
//#include <EGL/egl.h>
//#include <GLES/gl.h>

#include <jni.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state)
{
    // loop waiting for stuff to do.
    LOGI("Hello, Android world!");

    while (true) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // @note Block forever waiting for events due to '-1', use 0 if animating
        while ((ident = ALooper_pollAll(-1, nullptr, &events,(void**)&source)) >= 0) 
        {
            // Process this event.
            if (source != nullptr) 
                source->process(state, source);

            // Check if we are exiting.
            if (state->destroyRequested != 0)
                return;
        }
    }
}

#else

#include <iostream>
#include <string>

int main()
{
    std::cout << "Hello, world!\n";
}

#endif