/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Vibrator.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::android::hardware::vibrator::Vibrator;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    // make a default vibrator service
    auto vib = ndk::SharedRefBase::make<Vibrator>();
    const std::string vibName = std::string() + Vibrator::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(vib->asBinder().get(), vibName.c_str());
    CHECK_EQ(status, STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
