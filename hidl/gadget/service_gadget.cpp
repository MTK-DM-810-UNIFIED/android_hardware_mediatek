/*
 * SPDX-FileCopyrightText: 2021 The Android Open Source Project
 * SPDX-FileCopyrightText: 2024 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.usb.gadget-service.mediatek"

#include <hidl/HidlTransportSupport.h>
#include "UsbGadget.h"

using android::sp;

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::usb::gadget::V1_2::IUsbGadget;
using android::hardware::usb::gadget::V1_2::implementation::UsbGadget;

using android::OK;
using android::status_t;

int main() {
    android::sp<IUsbGadget> service = new UsbGadget();
    configureRpcThreadpool(2, true /*callerWillJoin*/);
    status_t status = service->registerAsService();

    if (status != OK) {
        ALOGE("Cannot register USB Gadget HAL service");
        return 1;
    }

    ALOGI("USB gadget HAL Ready.");
    joinRpcThreadpool();
    // Under noraml cases, execution will not reach this line.
    ALOGI("USB gadget HAL failed to join thread pool.");
    return 1;
}
